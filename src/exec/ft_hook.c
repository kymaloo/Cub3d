#include "cub.h"

void	ft_hook(void *data_game)
{
	t_game	*g;

	g = data_game;
	draw_frame(g);
	player_rotations(g);
	player_movements(g);
	ft_close_window(g);
}