#include "cub.h"
 
int	is_wall(t_map *map, int x, int y)
{
	if (x > map->x_max -1 || x < 0 || y > map->y_max -1 || y < 0) //if it's outside of the map, it's a wall now // max -1 ???
		return (1);
	if (isset(map->grid[y][x], "1D") == false)
		return (1);
	return (0);
}


static int	check_colors_for_map(char c)
{
	if (c == '1')
		return (C_WALL_BLACK);
	if (c == '0')
		return (C_FLOOR_BROWN);
	if (c == 'D')
		return (C_BLUE);
	return (C_GREY_INVALID);
}

static void	draw_square(t_game *g, int x, int y)
{
	int	i;
	int	j;

	i = 0;
	printf("%d\n", TILE_SIZE_MINIMAP);
	while (i < TILE_SIZE_MINIMAP)
	{
		j = 0;
		while (j < TILE_SIZE_MINIMAP)
		{
			//printf("%p\n", g->texture->image->img_window);
			mlx_put_pixel(g->texture->image->img_window, x + j, y + i, g->colors_minimap);
			j++;
		}
		i++;
	}
}

void	draw_map(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while(game->map->grid[y])
	{
		x = 0;
		while(game->map->grid[y][x])
		{
			game->colors_minimap = check_colors_for_map(game->map->grid[y][x]);
			draw_square(game, x * TILE_SIZE_MINIMAP, y * TILE_SIZE_MINIMAP);
			x++;
		}
		y++;
	}
}
