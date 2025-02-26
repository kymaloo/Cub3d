#include "cub.h"

// static void	draw_square(t_game *g, int x, int y, int size)
// {
// 	int	i;
// 	int	j;

// 	i = 0;
// 	while (i < size)
// 	{
// 		j = 0;
// 		while (j < size)
// 		{
// 			mlx_put_pixel(g->texture->image->img_window, \
// 				x + i, y + j, g->color);
// 			j++;
// 		}
// 		i++;
// 	}
// }

// void	draw_map(t_game *g)
// {
// 	int	x;
// 	int	y;
// 	int	xp;
// 	int	yp;

// 	xp = (g->player->position[X] / 16) - 5;
// 	yp = (g->player->position[Y] / 16) - 5;
// 	y = (g->player->position[Y] / 16) - 5;
// 	// while (count != 10)
// 	// {
// 	// 	x = (g->player->position[X] / 16) - 5;
// 	// 	count2 = 0;
// 	// 	while (count2 != 10)
// 	// 	{
// 	// 		g->color = check_colors_for_map(g->map->map[y][x]);
// 	// 		draw_square(g, x * g->map->tile_size, y * g->map->tile_size, g->map->tile_size);
// 	// 		x++;
// 	// 		count2++;
// 	// 	}
// 	// 	count++;
// 	// 	y++;
// 	// }

// 	y = 0;
// 	printf("[Y  ][X  ]\n");
// 	while (y != 16)
// 	{
// 		x = 0;
// 		while (x != 1)
// 		{																								
// 			printf("[%-3d][%-3d]\n", yp, xp);
// 			g->color = check_colors_for_map(yp, xp g->map->map);
// 			draw_square(g, x * g->map->tile_size, y * g->map->tile_size, g->map->tile_size);
// 			x++;
// 			xp++;
// 		}
// 		y++;
// 		yp++;
// 	}

// 	// y = 0;
// 	// while (g->map->map[y])
// 	// {
// 	// 	x = 0;
// 	// 	while (g->map->map[y][x])
// 	// 	{
// 	// 		g->color = check_colors_for_map(g->map->map[y][x]);
// 	// 		if (g->color != 0)
// 	// 			draw_square(g, x * g->map->tile_size, \
// 	// 			y * g->map->tile_size, g->map->tile_size);
// 	// 		x++;
// 	// 	}
// 	// 	y++;
// 	// }
// }



int	is_wall(char **map, int x, int y)
{
	if (isset(map[y][x], "1D") == false)
		return (1);
	return (0);
}
