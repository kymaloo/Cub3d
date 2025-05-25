#include "cub.h"

void	ft_keys_movement_translations(t_game *game)
{
	if (mlx_is_key_down(game->mlx, MLX_KEY_W) || mlx_is_key_down(game->mlx, MLX_KEY_UP))
	{
		move_translate_forward(game);
	}
	if (mlx_is_key_down(game->mlx, MLX_KEY_S) || mlx_is_key_down(game->mlx, MLX_KEY_DOWN))
	{
		move_translate_backward(game);
	}
	if (mlx_is_key_down(game->mlx, MLX_KEY_A))
	{
		move_translate_left(game);
	}
	if (mlx_is_key_down(game->mlx, MLX_KEY_D))
	{
		move_translate_right(game);
	}
}		

void	ft_keys_movement_rotations(t_game *game)
{
	bool rotated;
	
	rotated = false;
	if (mlx_is_key_down(game->mlx, MLX_KEY_RIGHT))
	{
		if (DEBUG)
			printf(BLUE"%15s:"YELLOW"%-3d:"RESET"%-15s:    "BBLUE"\t%4s\t"RESET"\n", __FILE__, __LINE__, __FUNCTION__, "ROTATE RIGHT");
		game->player->radian += 0.05;
		rotated = !rotated;
	}
	else if (mlx_is_key_down(game->mlx, MLX_KEY_LEFT))
	{
		if (DEBUG)
			printf(BLUE"%15s:"YELLOW"%-3d:"RESET"%-15s:    "BBLUE"\t%4s\t"RESET"\n", __FILE__, __LINE__, __FUNCTION__, "ROTATE LEFT");
		game->player->radian -= 0.05;
		rotated = !rotated;
	}
	if (rotated)
	{
		game->player->radian = normalize_angle(game->player->radian);
		update_player_direction(game->player);
	}
}

void	ft_keys_other_actions(t_game *game)
{
	if ((mlx_is_key_down(game->mlx, MLX_KEY_ESCAPE)) \
	|| (mlx_is_key_down(game->mlx, MLX_KEY_LEFT_CONTROL) && mlx_is_key_down(game->mlx, MLX_KEY_D)))
		mlx_close_window(game->mlx);
}

void	ft_keys_hook(mlx_key_data_t keydata, void *game_data)
{
	t_game *game;
	
	(void) keydata;
	game = game_data;
	ft_keys_movement_translations(game);
	ft_keys_movement_rotations(game);
	ft_keys_other_actions(game);
}