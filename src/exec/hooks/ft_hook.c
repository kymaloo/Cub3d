#include "cub.h"

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
	game_loop(data_game);
}