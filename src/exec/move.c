#include "cub.h"

void	ft_move_perso(t_game *g)
{
	g->player->position[X] = g->texture->image->player_img->instances[0].x;
	g->player->position[Y] = g->texture->image->player_img->instances[0].y;
	if (mlx_is_key_down(g->mlx, MLX_KEY_W))
	{
		g->texture->image->player_img->instances[0].x -= cos(g->player->radian) * 5;
		g->texture->image->player_img->instances[0].y -= sin(g->player->radian) * 5;
	}
	if (mlx_is_key_down(g->mlx, MLX_KEY_S))
	{
		g->texture->image->player_img->instances[0].x += cos(g->player->radian) * 5;
		g->texture->image->player_img->instances[0].y += sin(g->player->radian) * 5;
	}
	if (mlx_is_key_down(g->mlx, MLX_KEY_A))
	{
		g->texture->image->player_img->instances[0].x += cos(g->player->radian + M_PI/2) * 5;
		g->texture->image->player_img->instances[0].y += sin(g->player->radian + M_PI/2) * 5;
	}
	if (mlx_is_key_down(g->mlx, MLX_KEY_D))
	{
		g->texture->image->player_img->instances[0].x += cos(g->player->radian - M_PI/2) * 5;
		g->texture->image->player_img->instances[0].y += sin(g->player->radian - M_PI/2) * 5;
	}
}

int	ft_check_collision_top(t_game *g)
{
	int	x;
	int	y;

	x = g->player->position[X];
	y = g->player->position[Y];
	if (g->map->map[(y - 8) / 16] \
		[x / 16] == '1' || g->map->map[(y - 8) / 16] \
		[(x + 60) / 16] == '1')
		return (-1);
	return (0);
}

int	ft_check_collision_bot(t_game *g)
{
	int	x;
	int	y;

	x = g->player->position[X];
	y = g->player->position[Y];
	if (g->map->map[(y + 68) / 16] \
		[x / 16] == '1' || g->map->map[(y + 68) / 16] \
		[(x + 60) / 16] == '1')
		return (-1);
	return (0);
}

int	ft_check_collision_left(t_game *g)
{
	int	x;
	int	y;

	x = g->player->position[X];
	y = g->player->position[Y];
	if (g->map->map[y / 16] \
		[(x - 8) / 16] == '1' || g->map->map[(y + 60) / 16] \
		[(x - 8) / 16] == '1')
		return (-1);
	return (0);
}

int	ft_check_collision_right(t_game *g)
{
	int	x;
	int	y;

	x = g->player->position[X];
	y = g->player->position[Y];
	if (g->map->map[y / 16] \
		[(x + 68) / 16] == '1' || g->map->map[(y + 60) / 16] \
		[(x + 68) / 16] == '1')
		return (-1);
	return (0);
}
