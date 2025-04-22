#include "cub.h"

//TODO SOURIS ??
void	player_rotations(t_game *g)
{
	if (mlx_is_key_down(g->mlx_infos.mlx, MLX_KEY_RIGHT))
	g->player.angle += 0.05;
	if (mlx_is_key_down(g->mlx_infos.mlx, MLX_KEY_LEFT))
	g->player.angle -= 0.05;
}