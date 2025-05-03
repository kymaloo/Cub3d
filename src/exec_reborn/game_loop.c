#include "exec_reborn.h"

void	game_loop(t_game *g)
{
	//
	render_frame(&g->mlx_infos, g->player, &g->mlx_infos.textures, g->ray_collisions);
	player_rotations(g);
	// 1/60 s
	player_moves(g);
	keys_pressed(g);
}

void	ft_hook(void *data_game)
{
	game_loop(data_game);
}