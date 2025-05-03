#include "exec_reborn.h"

mouse_rotate(t_game *g)
{
	//get mouse coords,
	//put mouse back,
	//move the difference,
}

keyboard_rotate(t_game *g)
{
	if (mlx_is_key_down(g->mlx_infos.mlx, MLX_KEY_RIGHT))
		g->player.angle += 0.05;
	if (mlx_is_key_down(g->mlx_infos.mlx, MLX_KEY_LEFT))
		g->player.angle -= 0.05;
}

player_rotations(t_game *g)
{
	keyboard_rotate(g);
	mouse_rotate(g);
}