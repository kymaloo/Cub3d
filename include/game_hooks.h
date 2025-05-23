#ifndef GAME_HOOKS_H
#define GAME_HOOKS_H
#include "cub.h"

void	move_translate_forward(t_game *game);
void	move_translate_backward(t_game *game);
void	move_translate_left(t_game *game);
void	move_translate_right(t_game *game);

void	ft_keys_mouse_player_rotations(t_game *game, int32_t old_mouse_x, int32_t old_mouse_y);
void	ft_keys_other_actions(t_game *game);

bool	toggle_bool(bool *b);

#endif