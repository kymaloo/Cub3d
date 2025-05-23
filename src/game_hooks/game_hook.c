#include "cub.h"

void	ft_keys_player_movements(t_game *game)
{
	if (mlx_is_key_down(game->mlx, MLX_KEY_W) || mlx_is_key_down(game->mlx, MLX_KEY_UP))
	{
		move_translate_forward(game);
	}
	else if (mlx_is_key_down(game->mlx, MLX_KEY_S) || mlx_is_key_down(game->mlx, MLX_KEY_DOWN))
	{
		move_translate_backward(game);
	}
	if (mlx_is_key_down(game->mlx, MLX_KEY_A))
	{
		move_translate_left(game);
	}
	else if (mlx_is_key_down(game->mlx, MLX_KEY_D))
	{
		move_translate_right(game);
	}
}

/* HOOKS */

#include <unistd.h>     // for usleep()
#include <sys/time.h>   // for gettimeofday()

#define TARGET_FPS 60
#define FRAME_DURATION_US (1000000 / TARGET_FPS) // 16,666 microseconds

long long	get_time_us(void)
{
	struct timeval tv;
	gettimeofday(&tv, NULL);
	return ((long long)tv.tv_sec * 1000000LL + tv.tv_usec);
}

void	precise_sleep(long long target_us)
{
	long long start = get_time_us();
	long long now = get_time_us();

	// Sleep most of the time, then busy-wait for the final part
	if (target_us > 2000) // Skip usleep if total delay is very small
		usleep(target_us - 1000); // sleep all but last ~1ms

	now = get_time_us();
	while ((now - start) < target_us)
	{
		now = get_time_us();
	}
}

void	ft_hook(void *game_ptr)
{
	t_game	*game;
	static int32_t	old_mouse_x = 0;
	static int32_t	old_mouse_y = 0;
	long long start;
	
	start = get_time_us();
	game = game_ptr;


	ft_keys_player_movements(game);
	ft_keys_mouse_player_rotations(game, old_mouse_x, old_mouse_y);
	ft_keys_other_actions(game);


	//ft_move_perso(game);
	//print_minimap(game);
	raycast(game);

	long long end = get_time_us();
	long long elapsed = end - start;
	
	if (elapsed < FRAME_DURATION_US)
	precise_sleep(FRAME_DURATION_US - elapsed);
	mlx_get_mouse_pos(game->mlx, &old_mouse_x, &old_mouse_y);
}