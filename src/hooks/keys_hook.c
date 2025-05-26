#include "cub.h"



void	ft_keys_other_actions(mlx_key_data_t keydata, t_game *game)
{
    if (keydata.action == MLX_PRESS && (keydata.key == MLX_KEY_ESCAPE   
		|| (keydata.key == MLX_KEY_D && keydata.modifier & MLX_CONTROL)))
	{
		mlx_close_window(game->mlx);
	}
}

void	ft_keys_hook(mlx_key_data_t keydata, void *game_data)
{
	t_game *game;
	
	game = game_data;
	ft_keys_other_actions(keydata, game);
}