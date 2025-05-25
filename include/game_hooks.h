#ifndef GAME_HOOKS_H
#define GAME_HOOKS_H
#include "cub.h"

#define TARGET_FPS 60
#define FRAME_TIME (1.0 / TARGET_FPS)


/*utils*/
bool	toggle_bool(bool *b);

/*move utils*/
void	move_translate_forward(t_game *game);
void	move_translate_backward(t_game *game);
void	move_translate_left(t_game *game);
void	move_translate_right(t_game *game);

void	ft_keys_mouse_player_rotations(t_game *game, int32_t old_mouse_x, int32_t old_mouse_y);
void	ft_keys_other_actions(t_game *game);


/*hooks*/
void	ft_loop_hook(void *game_ptr);
void	ft_keys_hook(mlx_key_data_t keydata, void *game_data);
void	ft_cursor_hook(double xpos, double ypos, void *game_data);
void	ft_mouse_hook(mouse_key_t button, action_t action, modifier_key_t mods, void *param);
#endif