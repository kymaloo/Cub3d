#include "exec_reborn.h"

void	game_loop(t_game *g)
{
	//
	render_frame(g, &g->mlx_infos, &g->mlx_infos.textures, g->ray_collisions);
	player_rotations(g);
	player_moves(g);
	keys_pressed(g);
	// 1/60 s
}

void	ft_hook(void *data_game)
{
	game_loop(data_game);
}