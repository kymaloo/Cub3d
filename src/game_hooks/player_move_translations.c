#include "cub.h"
#define MOVE_SPEED 1
#define PLAYER_WIDTH 0.05

void	move_translate_forward(t_game *game)
{
	t_player *p = game->player;
	double new_x = p->position[X] + p->direction[X] * MOVE_SPEED;
	double new_y = p->position[Y] + p->direction[Y] * MOVE_SPEED;

	if (DEBUG)
	{
		print_debug_prefix(WHERE_FUNC, "UP");
		print_player_infos(game->player, "before");
		print_coord("trying to move to:", "", new_x, new_y);
	}
	if (!is_wall(game->map, new_x + PLAYER_WIDTH, new_y + PLAYER_WIDTH) &&
		!is_wall(game->map, new_x - PLAYER_WIDTH, new_y - PLAYER_WIDTH))
	{
		p->position[0] = new_x;
		p->position[1] = new_y;
	}
	else if (DEBUG)
	{
		printf(RED"\t\t\t(DENIED)"RESET"\n");
		//print_map_around(game, p->position[X],  p->position[Y], 5);
		print_map_around_a_highlight_b(game, p->position[X], p->position[Y], new_x, new_y, 5);
	}
	if (DEBUG)
		print_player_infos(game->player, "after");
}

void	move_translate_backward(t_game *game)
{
	t_player *p = game->player;
	double new_x = p->position[0] - p->direction[0] * MOVE_SPEED;
	double new_y = p->position[1] - p->direction[1] * MOVE_SPEED;

	if (!is_wall(game->map, new_x + PLAYER_WIDTH, new_y + PLAYER_WIDTH) &&
		!is_wall(game->map, new_x - PLAYER_WIDTH, new_y - PLAYER_WIDTH))
	{
		p->position[0] = new_x;
		p->position[1] = new_y;
	}
}

void	move_translate_left(t_game *game)
{
	t_player *p = game->player;
	double perp_x = -p->direction[1]; //perpendicular vector
	double perp_y = p->direction[0];

	double new_x = p->position[0] + perp_x * MOVE_SPEED;
	double new_y = p->position[1] + perp_y * MOVE_SPEED;

	if (!is_wall(game->map, new_x + PLAYER_WIDTH, new_y + PLAYER_WIDTH) &&
		!is_wall(game->map, new_x - PLAYER_WIDTH, new_y - PLAYER_WIDTH))
	{
		p->position[0] = new_x;
		p->position[1] = new_y;
	}
}

void	move_translate_right(t_game *game)
{
	t_player *p = game->player;
	double perp_x = p->direction[1];
	double perp_y = -p->direction[0];

	double new_x = p->position[0] + perp_x * MOVE_SPEED;
	double new_y = p->position[1] + perp_y * MOVE_SPEED;

	if (!is_wall(game->map, new_x + PLAYER_WIDTH, new_y + PLAYER_WIDTH) &&
		!is_wall(game->map, new_x - PLAYER_WIDTH, new_y - PLAYER_WIDTH))
	{
		p->position[0] = new_x;
		p->position[1] = new_y;
	}
}