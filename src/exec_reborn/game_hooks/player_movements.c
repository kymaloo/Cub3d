#include "exec_reborn.h"


static bool is_collision_at(t_game *g, float x, float y)
{
	int grid_x = x / TILE_SIZE;
	int grid_y = y / TILE_SIZE;
	return is_wall(g->map->map, grid_x, grid_y);
}

static void player_move_forward(t_game *g)
{
	float angle = g->player->angle;
	float px = g->player->position[X];
	float py = g->player->position[Y];

	// Position projetée pour collision
	float projected_x = px - cos(angle) * COLLISION_CHECK_DISTANCE;
	float projected_y = py - sin(angle) * COLLISION_CHECK_DISTANCE;

	// Déplacement si pas de mur sur l'axe X
	if (!is_collision_at(g, projected_x, py))
		g->texture->image->player_img->instances[0].x -= cos(angle) * PLAYER_MOVE_SPEED;

	// Déplacement si pas de mur sur l'axe Y
	if (!is_collision_at(g, px, projected_y))
		g->texture->image->player_img->instances[0].y -= sin(angle) * PLAYER_MOVE_SPEED;
}

static void player_move_backward(t_game *g)
{
	float angle = g->player->angle;
	float px = g->player->position[X];
	float py = g->player->position[Y];

	float projected_x = px - cos(angle) * COLLISION_CHECK_DISTANCE;
	float projected_y = py - sin(angle) * COLLISION_CHECK_DISTANCE;

	if (!is_collision_at(g, projected_x, py))
		g->texture->image->player_img->instances[0].x -= cos(angle) * PLAYER_MOVE_SPEED;

	if (!is_collision_at(g, px, projected_y))
		g->texture->image->player_img->instances[0].y -= sin(angle) * PLAYER_MOVE_SPEED;
}


static void player_strafe_left(t_game *g)
{
	float angle = g->player->angle - M_PI_2; // -90°
	float px = g->player->position[X];
	float py = g->player->position[Y];

	float projected_x = px + cos(angle) * COLLISION_CHECK_DISTANCE;
	float projected_y = py + sin(angle) * COLLISION_CHECK_DISTANCE;

	if (!is_collision_at(g, projected_x, py))
		g->texture->image->player_img->instances[0].x += cos(angle) * PLAYER_MOVE_SPEED;

	if (!is_collision_at(g, px, projected_y))
		g->texture->image->player_img->instances[0].y += sin(angle) * PLAYER_MOVE_SPEED;
}


static void player_strafe_right(t_game *g)
{
	float angle = g->player->angle + M_PI_2; // +90°
	float px = g->player->position[X];
	float py = g->player->position[Y];

	float projected_x = px + cos(angle) * COLLISION_CHECK_DISTANCE;
	float projected_y = py + sin(angle) * COLLISION_CHECK_DISTANCE;

	if (!is_collision_at(g, projected_x, py))
		g->texture->image->player_img->instances[0].x += cos(angle) * PLAYER_MOVE_SPEED;

	if (!is_collision_at(g, px, projected_y))
		g->texture->image->player_img->instances[0].y += sin(angle) * PLAYER_MOVE_SPEED;
}


void player_moves(t_game *g)
{
	g->player->position[X] = g->texture->image->player_img->instances[0].x + TILE_SIZE / 2;
	g->player->position[Y] = g->texture->image->player_img->instances[0].y + TILE_SIZE / 2;

	if (mlx_is_key_down(g->mlx_infos.mlx, MLX_KEY_W))
		player_move_forward(g);
	if (mlx_is_key_down(g->mlx_infos.mlx, MLX_KEY_S))
		player_move_backward(g);
	if (mlx_is_key_down(g->mlx_infos.mlx, MLX_KEY_A))
		player_strafe_left(g);
	if (mlx_is_key_down(g->mlx_infos.mlx, MLX_KEY_D))
		player_strafe_right(g);
}
