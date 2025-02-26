#include "cub.h"

int	is_map_coord_valid(t_map *map_infos, int x, int y)
{
	if (x < 0 || x > map_infos->x_max \
		|| y < 0 || y > map_infos->y_max)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	map_block_color(t_map *map, int x, int y)
{
	if (is_map_coord_valid(map, x, y) == EXIT_FAILURE)
		return (COLOR_OUT_OF_BOUNDS);
	else if (map->map[y][x] == '1')
		return (COLOR_WALL);
	else if (map->map[y][x] == '0')
		return (COLOR_FLOOR);
	else if (map->map[y][x] == 'D')
		return (COLOR_DOOR);
	else if (map->map[y][x] == ' ')
		return (COLOR_VOID);
	else
		return (COLOR_INVALID);
}

static void	draw_square_tab(mlx_image_t *img_window, int square_color, int where_to_draw[], int len_square_side)
{
	int	draw_coords[DIM];
	int	i;
	int	j;

	draw_coords[X] *= GRID_SIZE_X;
	draw_coords[Y] *= GRID_SIZE_Y;
	i = 0;
	while (i < len_square_side)
	{
		j = 0;
		while (j < len_square_side)
		{
			mlx_put_pixel(img_window, where_to_draw[X] + i, \
										where_to_draw[Y] + j, square_color);
			j++;
		}
		i++;
	}
}


void	draw_radar_from(t_game *g, int radar_top_left[])
{
	int	block_player[DIM];
	int	block_to_draw[DIM];
	int	draw_where[DIM];
	
	block_player[Y] = (int) g->player->position[Y] / RADAR_SQUARE_SIDE;
	block_player[X] = (int) g->player->position[X] / RADAR_SQUARE_SIDE;
	draw_where[Y] = radar_top_left[X];
	
	block_to_draw[Y] = block_player[Y] - RADAR_BLOCKS_RADIUS;
	while(block_to_draw[Y] < block_player[Y] + RADAR_BLOCKS_RADIUS + 1)
	{
		block_to_draw[X] = block_player[X] - RADAR_BLOCKS_RADIUS;
		draw_where[X] = radar_top_left[Y];
		while(block_to_draw[X] < block_player[X] + RADAR_BLOCKS_RADIUS + 1)
		{
			draw_square_tab(g->texture->image->img_window, \
				map_block_color(g->map, block_to_draw[X], block_to_draw[Y]), \
				draw_where, RADAR_SQUARE_SIDE);
				block_to_draw[X]++;
				draw_where[X]+= RADAR_SQUARE_SIDE;
			}
			block_to_draw[Y]++;
			draw_where[Y]+= RADAR_SQUARE_SIDE;
		}
}

// Function to draw a filled circle (disc) using while loops
void drawDisc(t_game *g, int center[], int radius, int color) {
	int y = -radius;  // Start at the bottom of the circle

	while (y <= radius)
	{
		int x_max = (int)sqrt(radius * radius - y * y);
		int x = -x_max;
		while (x <= x_max)
		{
			mlx_put_pixel(g->texture->image->img_window, center[X] + x, \
				center[Y] + y, color);
			x++;
		}
		y++;
	}
}


void	draw_radar_player(t_game *g)
{
	int	center[DIM];

	center[Y] = (RADAR_BLOCKS_RADIUS + 1) * RADAR_SQUARE_SIDE;
	center[X] = (RADAR_BLOCKS_RADIUS + 1) * RADAR_SQUARE_SIDE;
	drawDisc(g, center, RADAR_PLAYER_CIRCLE_RADIUS, COLOR_PLAYER);
}

void	draw_radar(t_game *g)
{
	int	radar_pos[DIM];
	int	player_pos[DIM];
	int	where_to_draw[DIM];

	init_coords(radar_pos, RADAR_POS_X, RADAR_POS_Y); //verifier arpes parsing
	where_to_draw[X] = (radar_pos[X] + RADAR_BLOCKS_RADIUS + 1) * RADAR_SQUARE_SIDE;
	where_to_draw[Y] = (radar_pos[Y] + RADAR_BLOCKS_RADIUS + 1) * RADAR_SQUARE_SIDE;

	draw_radar_from(g, radar_pos);
	init_coords(player_pos, g->player->position[X],  g->player->position[Y]);
	draw_square_tab(g->texture->image->img_window, 0x0002255FF, where_to_draw, RADAR_SQUARE_SIDE);
	draw_radar_player(g);
}