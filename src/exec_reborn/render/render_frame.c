#include "exec_reborn.h"

/**
 * @brief Clears the walls image with transparency
 * @param walls Pointer to walls image buffer
 */
static void	clear_walls_image(mlx_image_t *walls)
{
	size_t		total_pixels;
	uint32_t	*pixels;

	pixels = (uint32_t *) walls->pixels;
	total_pixels = walls->width * walls->height;
	while (total_pixels--)
	{
		*pixels++ = 0x00000000;
	}
}

/**
 * @brief Calculates wall rendering dimensions
 * @param col Collision information pointer
 * @param height Output parameter for wall height
 * @param start Output parameter for draw start Y position
 * @param end Output parameter for draw end Y position
 */
static void	calculate_wall_dimensions(t_collision_infos *col, float *height, \
														int *start, int *end)
{
	float	wall_height;
	int		draw_start;
	int		draw_end;
	float	fov_correction;

	fov_correction = SCREEN_WIDTH / 1.15f;
	wall_height = (TILE_SIZE / col->wall_distance) * fov_correction;
	draw_start = (SCREEN_HEIGHT - wall_height) / 2;
	draw_end = (SCREEN_HEIGHT + wall_height) / 2;
	if (draw_start < 0)
	{
		draw_start = 0;
	}
	if (draw_end >= SCREEN_HEIGHT)
	{
		draw_end = SCREEN_HEIGHT - 1;
	}
	*height = wall_height;
	*start = draw_start;
	*end = draw_end;
}

uint32_t	mlx_get_texture_pixel(mlx_texture_t *tex, unsigned int tex_x, unsigned int tex_y)
{
	uint8_t		*pixel_ptr;
	uint32_t	color;

	// Check bounds
	if (tex == NULL || tex_x >= tex->width || tex_y >= tex->height)
		return (COLOR_MISSING);

	// Calculate pixel position (4 bytes per pixel: RGBA)
	pixel_ptr = &tex->pixels[(tex_y * tex->width + tex_x) * 4];

	// Pack into 32-bit ARGB format
	color = 0;
	color |= (uint32_t)pixel_ptr[3] << 24; // Alpha
	color |= (uint32_t)pixel_ptr[0] << 16; // Red
	color |= (uint32_t)pixel_ptr[1] << 8;  // Green
	color |= (uint32_t)pixel_ptr[2];       // Blue

	return (color);
}

static void	draw_textured_column(mlx_image_t *walls, mlx_texture_t *tex, 
							t_collision_infos *col, int x)
{
	float		wall_height;
	int			draw_start;
	int			draw_end;
	int			tex_x;
	int			tex_y;
	int			y;
	uint32_t	color;

	calculate_wall_dimensions(col, &wall_height, &draw_start, &draw_end);
	tex_x = (int)(col->wall_hit_pos * tex->width);
	y = draw_start;
	while (y < draw_end)
	{
		tex_y = (int)((y - draw_start) * tex->height / wall_height);
		color = mlx_get_texture_pixel(tex, tex_x, tex_y);
		mlx_put_pixel(walls, x, y, color);
		y++;
	}
}

static void	draw_missing_texture_marker(mlx_image_t *walls, t_collision_infos *col, int x)
{
	int	y;

	(void) col;
	y = 0;
	while (y < SCREEN_HEIGHT)
		mlx_put_pixel(walls, x, y++, COLOR_MISSING);
}

mlx_texture_t	*select_wall_texture(t_textures *tex, t_wall_direction face)
{
	if (face == NORTH)
		return (tex->wall_north);
	else if(face == SOUTH)
		return (tex->wall_south);
	else if(face == EAST)
		return (tex->wall_east);
	else if(face == WEST)
		return (tex->wall_west);
	else
		nuclear_exit(ft_error(__FILE__, __LINE__, "bad wall_face", EXIT_FAILURE));
	return (NULL);
}

void	draw_walls_textures(mlx_image_t *walls, t_textures *tex, t_collision_infos *collisions)
{
	int				x;
	mlx_texture_t	*wall_tex;

	x = 0;
	while (x < SCREEN_WIDTH)
	{
		if (collisions[x].face != NO_COLLISION)
		{
			wall_tex = select_wall_texture(tex, collisions[x].face);
			if (wall_tex != NULL)
				draw_textured_column(walls, wall_tex, &collisions[x], x);
			else
				draw_missing_texture_marker(walls, &collisions[x], x);
		}
		x++;
	}
}

void	draw_walls_colors_only(mlx_image_t *walls, t_collision_infos *collisions)
{
	int	x;
	int	y;

	x = 0;
	while (x < SCREEN_WIDTH)
	{
		y = 0;
		if (collisions[x].face != NO_COLLISION)
		{
			if (collisions->face == NORTH)
			{
				while (y < SCREEN_HEIGHT)
					mlx_put_pixel(walls, x, y++, 0xFF0000FF); //R
			}
			else if (collisions->face == SOUTH)
			{
				while (y < SCREEN_HEIGHT)
					mlx_put_pixel(walls, x, y++, 0x00FF00FF); //G
			}
			else if (collisions->face == EAST)
			{
				while (y < SCREEN_HEIGHT)
					mlx_put_pixel(walls, x, y++, 0x0000FFFF); //B
			}
			else if (collisions->face == WEST)
			{
				while (y < SCREEN_HEIGHT)
					mlx_put_pixel(walls, x, y++, 0x000000FF); //W
			}
			else
			{
				while (y < SCREEN_HEIGHT)
					mlx_put_pixel(walls, x, y++, COLOR_MISSING); //V
			}
		}
		else
		{
			while (y < SCREEN_HEIGHT)
				mlx_put_pixel(walls, x, y++, COLOR_MISSING); //V
		}
		x++;
	}
}

//todo fixme
void	init_renderer(t_mlx_infos *m)
{
	int			x;
	int			y;
	uint32_t	color;

	m->images.background = mlx_new_image(m->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	y = 0;
	while (y < SCREEN_HEIGHT)
	{
		x = 0;
		while (x < SCREEN_WIDTH)
		{
			if (y < SCREEN_HEIGHT / 2)
				color = 0xBC7488FF;	//color = m->colors.color_floor;
			else
				color = 0x2D50FCFF;	//m->colors.color_ceiling;
			mlx_put_pixel(m->images.background, x, y, color);
			x++;
		}
		y++;
	}
	mlx_image_to_window(m->mlx, m->images.background, 0, 0);
	
	m->images.walls = mlx_new_image(m->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	mlx_image_to_window(m->mlx, m->images.walls, 0, 0);
}

void	render_frame(t_game *g, t_mlx_infos *m, t_textures *t, t_collision_infos *c)
{
	(void) t;
	raycast(g, &g->player, c);
	clear_walls_image(m->images.walls);
	draw_walls_colors_only(m->images.walls, c);
}