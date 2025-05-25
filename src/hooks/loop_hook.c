#include "cub.h"

/* HOOKS */
void	ft_loop_hook(void *game_ptr)
{
	t_game	*game;
	static double last_time = 0;
    double current_time;
	
	current_time = mlx_get_time();
    if ((current_time - last_time) < FRAME_TIME)
        return ;

    last_time = current_time;
	game = game_ptr;

	raycast(game);
}