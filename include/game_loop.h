#ifndef GAME_LOOP_H
#define GAME_LOOP_H

void	game_loop(t_game *g);
void	ft_hook(void *data_game);
void	player_moves(t_game *g);
void	player_rotations(t_game *g);

enum e_player_infos
{
	MOVE_SPEED = 1,
	PLAYER_WIDTH = 10,
};

#endif