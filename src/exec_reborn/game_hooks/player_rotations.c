#include "exec_reborn.h"

void	mouse_rotate(t_game *g)
{
	(void) g;
	printf("\tplayer rotation: "BBLUE"rotate\n"RESET);
	//get mouse coords,
	//put mouse back,
	//move the difference,
}

void	keyboard_rotate(t_game *g)
{
	if (mlx_is_key_down(g->mlx_infos.mlx, MLX_KEY_RIGHT))
	{
		//g->player.angle += 0.05;
		printf("\tplayer rotation: "BBLUE"right\n"RESET);
	}
	if (mlx_is_key_down(g->mlx_infos.mlx, MLX_KEY_LEFT))
	{
		//g->player.angle -= 0.05;
		printf("\tplayer rotation: "BBLUE"left\n"RESET);
	}
}

void	player_rotations(t_game *g)
{
	keyboard_rotate(g);
	mouse_rotate(g);
}