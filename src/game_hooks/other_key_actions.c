#include "cub.h"

void	ft_keys_other_actions(t_game *game)
{
	static bool catched_cursor = true;

	if ((mlx_is_key_down(game->mlx, MLX_KEY_ESCAPE)) \
	|| (mlx_is_key_down(game->mlx, MLX_KEY_LEFT_CONTROL) && mlx_is_key_down(game->mlx, MLX_KEY_D)))
		mlx_close_window(game->mlx);

	//TODO mlx_keyhook this bitch -
	if ((mlx_is_key_down(game->mlx, MLX_KEY_LEFT_CONTROL) && mlx_is_key_down(game->mlx, MLX_KEY_X)))
	{
		toggle_bool(&catched_cursor);
		if (catched_cursor)
			mlx_set_cursor_mode(game->mlx, MLX_MOUSE_DISABLED);
		else
			mlx_set_cursor_mode(game->mlx, MLX_MOUSE_NORMAL);
		printf(BGMAGENTA BLUE"CUROR CATCH IS NOW:  ");
		(catched_cursor)?printf(BGREEN"ON"RESET"\n"): printf(BRED"OFF"RESET"\n");
	}
}