#include "cub.h"

static void	move_left(t_game *g)
{
	int	xcos;
	int	ycos;
	int	xsin;
	int	ysin;

	if (mlx_is_key_down(g->mlx, MLX_KEY_A))
	{
		xcos = (g->player->position[X] - cos(g->player->radian) * DETECTION_RANGE) / TILE_SIZE;
		ycos = g->player->position[Y] / TILE_SIZE;
		xsin = g->player->position[X] / TILE_SIZE;
		ysin = (g->player->position[Y] - sin(g->player->radian) * DETECTION_RANGE) / TILE_SIZE;
		if (is_wall(g->map->grid, xcos, ycos))
			g->texture->image->player_img->instances[0].x -= cos(g->player->radian) * PLAYER_ADJUSTMENT;
		if (is_wall(g->map->grid, xsin, ysin))
			g->texture->image->player_img->instances[0].y -= sin(g->player->radian) * PLAYER_ADJUSTMENT;
	}
}

static void	move_right(t_game *g)
{
	int	xcos;
	int	ycos;
	int	xsin;
	int	ysin;

	if (mlx_is_key_down(g->mlx, MLX_KEY_D))
	{
		xcos = (g->player->position[X] + cos(g->player->radian) * DETECTION_RANGE) / TILE_SIZE;
		ycos = g->player->position[Y] / TILE_SIZE;
		xsin = g->player->position[X] / TILE_SIZE;
		ysin = (g->player->position[Y] + sin(g->player->radian) * DETECTION_RANGE) / TILE_SIZE;
		if (is_wall(g->map->grid, xcos, ycos))
			g->texture->image->player_img->instances[0].x += cos(g->player->radian) * PLAYER_ADJUSTMENT;
		if (is_wall(g->map->grid, xsin, ysin))
			g->texture->image->player_img->instances[0].y += sin(g->player->radian) * PLAYER_ADJUSTMENT;
	}
}

static void	move_bot(t_game *g)
{
	int	xcos;
	int	ycos;
	int	xsin;
	int	ysin;

	if (mlx_is_key_down(g->mlx, MLX_KEY_S))
	{
		xcos = (g->player->position[X] + cos(g->player->radian + M_PI / 2) * DETECTION_RANGE) / TILE_SIZE;
		ycos = g->player->position[Y] / TILE_SIZE;
		xsin = g->player->position[X] / TILE_SIZE;
		ysin = (g->player->position[Y] + sin(g->player->radian + M_PI / 2) * DETECTION_RANGE) / TILE_SIZE;
		if (is_wall(g->map->grid, xcos, ycos))
			g->texture->image->player_img->instances[0].x += cos(g->player->radian + M_PI / 2) * PLAYER_ADJUSTMENT;
		if (is_wall(g->map->grid, xsin, ysin))
			g->texture->image->player_img->instances[0].y += sin(g->player->radian + M_PI / 2) * PLAYER_ADJUSTMENT;
	}
}

static void	move_top(t_game *g)
{
	int	xcos;
	int	ycos;
	int	xsin;
	int	ysin;

	if (mlx_is_key_down(g->mlx, MLX_KEY_W))
	{
		xcos = (g->player->position[X] - cos(g->player->radian + M_PI / 2) * DETECTION_RANGE) / TILE_SIZE;
		ycos = g->player->position[Y] / TILE_SIZE;
		xsin = g->player->position[X] / TILE_SIZE;
		ysin = (g->player->position[Y] - sin(g->player->radian + M_PI / 2) * DETECTION_RANGE) / TILE_SIZE;
		if (is_wall(g->map->grid, xcos, ycos))
			g->texture->image->player_img->instances[0].x -= cos(g->player->radian + M_PI / 2) * PLAYER_ADJUSTMENT;
		if (is_wall(g->map->grid, xsin, ysin))
			g->texture->image->player_img->instances[0].y -= sin(g->player->radian + M_PI / 2) * PLAYER_ADJUSTMENT;
	}
}

void	ft_move_perso(t_game *g)
{
	g->player->position[X] = g->texture->image->player_img->instances[0].x + TILE_SIZE / 2;
	g->player->position[Y] = g->texture->image->player_img->instances[0].y + TILE_SIZE / 2;
	move_top(g);
	move_bot(g);
	move_left(g);
	move_right(g);
}
