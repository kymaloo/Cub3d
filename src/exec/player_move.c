#include "cub.h"

static void	move_top(t_game *g)
{
	if (mlx_is_key_down(g->mlx, MLX_KEY_W))
	{
		print_minimap(g);
		if (is_wall(g->map->map, (g->player->position[X] - \
			cos(g->player->angle) * 10) / 16, g->player->position[Y] / 16))
			g->texture->image->player_img->instances[0].x -= \
			cos(g->player->angle) * 5;
		if (is_wall(g->map->map, g->player->position[X] / 16, \
			(g->player->position[Y] - sin(g->player->angle) * 10) / 16))
			g->texture->image->player_img->instances[0].y -= \
			sin(g->player->angle) * 5;
	}
}

static void	move_bot(t_game *g)
{
	if (mlx_is_key_down(g->mlx, MLX_KEY_S))
	{
		print_minimap(g);
		if (is_wall(g->map->map, (g->player->position[X] + \
			cos(g->player->angle) * 10) / 16, g->player->position[Y] / 16))
			g->texture->image->player_img->instances[0].x += \
			cos(g->player->angle) * 5;
		if (is_wall(g->map->map, g->player->position[X] / 16, \
			(g->player->position[Y] + sin(g->player->angle) * 10) / 16))
			g->texture->image->player_img->instances[0].y += \
			sin(g->player->angle) * 5;
	}
}

static void	move_left(t_game *g)
{
	if (mlx_is_key_down(g->mlx, MLX_KEY_A))
	{
		print_minimap(g);
		if (is_wall(g->map->map, (g->player->position[X] + \
			cos(g->player->angle + M_PI / 2) * 10) / 16, \
		g->player->position[Y] / 16))
			g->texture->image->player_img->instances[0].x += \
			cos(g->player->angle + M_PI / 2) * 5;
		if (is_wall(g->map->map, g->player->position[X] / 16, \
			(g->player->position[Y] + sin(g->player->angle + M_PI / 2) \
			* 10) / 16))
			g->texture->image->player_img->instances[0].y += \
			sin(g->player->angle + M_PI / 2) * 5;
	}
}

static void	move_right(t_game *g)
{
	if (mlx_is_key_down(g->mlx, MLX_KEY_D))
	{
		print_minimap(g);
		if (is_wall(g->map->map, (g->player->position[X] - \
			cos(g->player->angle + M_PI / 2) * 10) / 16, \
			g->player->position[Y] / 16))
			g->texture->image->player_img->instances[0].x -= \
			cos(g->player->angle + M_PI / 2) * 5;
		if (is_wall(g->map->map, g->player->position[X] / 16, \
			(g->player->position[Y] - sin(g->player->angle + M_PI / 2) * \
			10) / 16))
			g->texture->image->player_img->instances[0].y -= \
			sin(g->player->angle + M_PI / 2) * 5;
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


//

void try_move_up(t_game *g)
{
	double would_move_to[NB_DIM];

	would_move_to[X] =
	would_move_to[Y] = 
	if (!is_wall(g->map->map, would_move_to[X], would_move_to[Y]))
	{
		g->player->position[X] = would_move_to[X];
		g->player->position[Y] = would_move_to[Y];
	}
}
void try_move_up(t_game *g)
{
	double would_move_to[NB_DIM];

	would_move_to[X] =
	would_move_to[Y] = 
	if (!is_wall(g->map->map, would_move_to[X], would_move_to[Y]))
	{
		g->player->position[X] = would_move_to[X];
		g->player->position[Y] = would_move_to[Y];
	}
}

void try_move_up(t_game *g)
{
	double would_move_to[NB_DIM];

	would_move_to[X] =
	would_move_to[Y] = 
	if (!is_wall(g->map->map, would_move_to[X], would_move_to[Y]))
	{
		g->player->position[X] = would_move_to[X];
		g->player->position[Y] = would_move_to[Y];
	}
}
void try_move_up(t_game *g)
{
	double would_move_to[NB_DIM];

	would_move_to[X] = player_move(g, X, UP);
	would_move_to[Y] = player_move(g, Y, UP);
	if (!is_wall(g->map->map, would_move_to[X], would_move_to[Y]))
	{
		g->player->position[X] = would_move_to[X];
		g->player->position[Y] = would_move_to[Y];
	}
}

void	ft_check_move(t_game *g)
{
	if (mlx_is_key_down(g->mlx, MLX_KEY_W))
		try_move_up(g);
	if (mlx_is_key_down(g->mlx, MLX_KEY_A))
		try_move_down(g);
	if (mlx_is_key_down(g->mlx, MLX_KEY_S))
		try_move_left(g);
	if (mlx_is_key_down(g->mlx, MLX_KEY_D))
		try_move_right(g);
}
