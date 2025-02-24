#include "cub.h"

static int	check_colors_for_map(char c)
{
	if (c == '1')
		return (C_BLACK);
	if (c == '0')
		return (C_BROWN);
	if (c == 'D')
		return (C_BLUE);
	return (0);
}

static void	draw_square(t_game *g, int x, int y, int size)
{
	int	i;
	int	j;

	i = 0;
	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			mlx_put_pixel(g->img_window, x + i, y + j, g->color);
			j++;
		}
		i++;
	}
}

void	draw_map(t_game *g)
{
	int	x;
	int	y;

	y = 0;
	while (g->map->map[y])
	{
		x = 0;
		while (g->map->map[y][x])
		{
			g->color = check_colors_for_map(g->map->map[y][x]);
			if (g->color != 0)
				draw_square(g, x * g->map->tile_size, \
				y * g->map->tile_size, g->map->tile_size);
			x++;
		}
		y++;
	}
}
