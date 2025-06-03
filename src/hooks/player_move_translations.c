#include "cub.h"
#define MOVE_SPEED 0.3
#define PLAYER_WIDTH 0.05

void	move_translate_forward(t_game *game)
{
	t_player *p;
	float new_x;
	float new_y;

	p = game->player;
	new_x = p->position[X] + p->direction[X] * MOVE_SPEED;
	new_y = p->position[Y] + p->direction[Y] * MOVE_SPEED;
	if (DEBUG_KEYS)
	{
		print_debug_prefix(WHERE_FUNC, "UP");
		print_player_infos(game->player, "before");
		print_coord("trying to move to:", "", new_x, new_y);
		print_map_player(game, 5);
	}
	if (!is_wall(game->map, new_x + PLAYER_WIDTH, new_y + PLAYER_WIDTH) &&
    	!is_wall(game->map, new_x - PLAYER_WIDTH, new_y + PLAYER_WIDTH) &&
    	!is_wall(game->map, new_x + PLAYER_WIDTH, new_y - PLAYER_WIDTH) &&
    	!is_wall(game->map, new_x - PLAYER_WIDTH, new_y - PLAYER_WIDTH))
	{
		if (DEBUG_KEYS)
			printf(GREEN"\t\t\t(ALLOWED)"RESET"\n");
		
		p->position[X] = new_x;
		p->position[Y] = new_y;
	}
	else if (DEBUG_KEYS)
		printf(RED"\t\t\t(DENIED)"RESET"\n");
	if (DEBUG_KEYS)
		print_player_infos(game->player, "after");
}

void	move_translate_backward(t_game *game)
{
	t_player *p;
	float new_x;
	float new_y;

	
	p = game->player;
	new_x = p->position[X] - (p->direction[X] * MOVE_SPEED);
	new_y = p->position[Y] - (p->direction[Y] * MOVE_SPEED);

	if (DEBUG_KEYS)
	{
    	print_debug_prefix(WHERE_FUNC, "DOWN");
    	print_player_infos(game->player, "before");
    	print_coord("trying to move to:", "", new_x, new_y);
		print_map_player(game, 5);
	}
	if (!is_wall(game->map, new_x + PLAYER_WIDTH, new_y + PLAYER_WIDTH) &&
    	!is_wall(game->map, new_x - PLAYER_WIDTH, new_y + PLAYER_WIDTH) &&
    	!is_wall(game->map, new_x + PLAYER_WIDTH, new_y - PLAYER_WIDTH) &&
    	!is_wall(game->map, new_x - PLAYER_WIDTH, new_y - PLAYER_WIDTH))
	{
		p->position[X] = new_x;
		p->position[Y] = new_y;
	}
	if (DEBUG_KEYS)
    	print_player_infos(game->player, "after");
}

void	move_translate_left(t_game *game)
{
	t_player *p = game->player;
	float new_x;
	float new_y;

	new_x = p->position[X] + (p->direction[Y] * MOVE_SPEED);
	new_y = p->position[Y] - (p->direction[X] * MOVE_SPEED);

	if (DEBUG_KEYS)
	{
    	print_debug_prefix(WHERE_FUNC, "LEFT");
    	print_player_infos(game->player, "before");
    	print_coord("trying to move to:", "", new_x, new_y);
		print_map_player(game, 5);
	}
	if (!is_wall(game->map, new_x + PLAYER_WIDTH, new_y + PLAYER_WIDTH) &&
    	!is_wall(game->map, new_x - PLAYER_WIDTH, new_y + PLAYER_WIDTH) &&
    	!is_wall(game->map, new_x + PLAYER_WIDTH, new_y - PLAYER_WIDTH) &&
    	!is_wall(game->map, new_x - PLAYER_WIDTH, new_y - PLAYER_WIDTH))
	{
		p->position[X] = new_x;
		p->position[Y] = new_y;
	}
	if (DEBUG_KEYS)
    	print_player_infos(game->player, "after");
}

void	move_translate_right(t_game *game)
{
	t_player *p = game->player;
	float new_x;
	float new_y;

	new_x = p->position[X] - (p->direction[Y] * MOVE_SPEED);
	new_y = p->position[Y] + (p->direction[X] * MOVE_SPEED);

	if (DEBUG_KEYS)
	{
    	print_debug_prefix(WHERE_FUNC, "RIGHT");
    	print_player_infos(game->player, "before");
    	print_coord("trying to move to:", "", new_x, new_y);
		print_map_player(game, 5);
	}
	if (!is_wall(game->map, new_x + PLAYER_WIDTH, new_y + PLAYER_WIDTH) &&
    	!is_wall(game->map, new_x - PLAYER_WIDTH, new_y + PLAYER_WIDTH) &&
    	!is_wall(game->map, new_x + PLAYER_WIDTH, new_y - PLAYER_WIDTH) &&
    	!is_wall(game->map, new_x - PLAYER_WIDTH, new_y - PLAYER_WIDTH))
	{
		p->position[X] = new_x;
		p->position[Y] = new_y;
	}
	if (DEBUG_KEYS)
    	print_player_infos(game->player, "after");
}