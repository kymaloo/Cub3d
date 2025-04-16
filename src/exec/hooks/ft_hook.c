#include "cub.h"

static void	ft_close_window(t_game *game)
{
	if (mlx_is_key_down(game->mlx_infos.mlx, MLX_KEY_ESCAPE))
		mlx_close_window(game->mlx_infos.mlx);
}

void	print_minimap(t_game *g)
{
	if (mlx_is_key_down(g->mlx_infos.mlx, MLX_KEY_M))
	{
		g->mlx_infos.images.minimap->enabled = true;
		g->mlx_infos.images.minimap_player->enabled = true;
	}
	else if (mlx_is_key_down(g->mlx_infos.mlx, MLX_KEY_N))
	{
		g->mlx_infos.images.minimap->enabled = true;
		g->mlx_infos.images.minimap_player->enabled = true;
	}
}
void	ft_hook(void *data_game)
{
	t_game	*g;

	g = data_game;
	draw_frame(g);
	player_rotations(g);
	player_movements(g);
	ft_close_window(g);
}