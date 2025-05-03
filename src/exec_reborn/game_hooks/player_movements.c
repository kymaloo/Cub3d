#include "exec_reborn.h"

player_move_forward()
{

}

player_move_backwards()
{

}

player_move_left()
{

}

player_move_right()
{

}

player_moves(t_game *g)
{
	if (mlx_is_key_down(g->mlx_infos.mlx, MLX_KEY_W))
		try_move_up(g);
	if (mlx_is_key_down(g->mlx_infos.mlx, MLX_KEY_A))
		try_move_down(g);
	if (mlx_is_key_down(g->mlx_infos.mlx, MLX_KEY_S))
		try_move_left(g);
	if (mlx_is_key_down(g->mlx_infos.mlx, MLX_KEY_D))
		try_move_right(g);
}