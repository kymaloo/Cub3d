#include "cub.h"

static void	move_top(t_game *g)
{
	if (mlx_is_key_down(g->mlx, MLX_KEY_W))
	{
		if (is_wall(g->map->map, (g->player->position[X] - \
			cos(g->player->radian) * 10) / 16, g->player->position[Y] / 16))
			g->texture->image->player_img->instances[0].x -= \
			cos(g->player->radian) * 5;
		if (is_wall(g->map->map, g->player->position[X] / 16, \
			(g->player->position[Y] - sin(g->player->radian) * 10) / 16))
			g->texture->image->player_img->instances[0].y -= \
			sin(g->player->radian) * 5;
	}
}

static void	move_bot(t_game *g)
{
	if (mlx_is_key_down(g->mlx, MLX_KEY_S))
	{
		if (is_wall(g->map->map, (g->player->position[X] + \
			cos(g->player->radian) * 10) / 16, g->player->position[Y] / 16))
			g->texture->image->player_img->instances[0].x += \
			cos(g->player->radian) * 5;
		if (is_wall(g->map->map, g->player->position[X] / 16, \
			(g->player->position[Y] + sin(g->player->radian) * 10) / 16))
			g->texture->image->player_img->instances[0].y += \
			sin(g->player->radian) * 5;
	}
}

static void	move_left(t_game *g)
{
	if (mlx_is_key_down(g->mlx, MLX_KEY_A))
	{
		if (is_wall(g->map->map, (g->player->position[X] + \
			cos(g->player->radian + M_PI / 2) * 10) / 16, \
		g->player->position[Y] / 16))
			g->texture->image->player_img->instances[0].x += \
			cos(g->player->radian + M_PI / 2) * 5;
		if (is_wall(g->map->map, g->player->position[X] / 16, \
			(g->player->position[Y] + sin(g->player->radian + M_PI / 2) \
			* 10) / 16))
			g->texture->image->player_img->instances[0].y += \
			sin(g->player->radian + M_PI / 2) * 5;
	}
}

static void	move_right(t_game *g)
{
	if (mlx_is_key_down(g->mlx, MLX_KEY_D))
	{
		if (is_wall(g->map->map, (g->player->position[X] - \
			cos(g->player->radian + M_PI / 2) * 10) / 16, \
			g->player->position[Y] / 16))
			g->texture->image->player_img->instances[0].x -= \
			cos(g->player->radian + M_PI / 2) * 5;
		if (is_wall(g->map->map, g->player->position[X] / 16, \
			(g->player->position[Y] - sin(g->player->radian + M_PI / 2) * \
			10) / 16))
			g->texture->image->player_img->instances[0].y -= \
			sin(g->player->radian + M_PI / 2) * 5;
	}
}

void	ft_move_perso(t_game *g)
{
	g->player->position[X] = g->texture->image->player_img->instances[0].x + 8;
	g->player->position[Y] = g->texture->image->player_img->instances[0].y + 8;
	move_top(g);
	move_bot(g);
	move_left(g);
	move_right(g);
}
