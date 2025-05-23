#include "cub.h"

void	update_player_direction(t_player *player)
{
	player->direction[0] = cos(player->radian); // X component
	player->direction[1] = sin(player->radian); // Y component
}
#define	MOUSE_SENSITIVITY 0.005
#define MOUSE_MOUVEMENT_DETECTION_THRESHOLD 4

bool	toggle_bool(bool *b)
{
	if (*b)
		*b = false;
	else
		*b = true;
	return (*b);
}

float normalize_angle(float angle) 
{
    while (angle < 0)
		angle += 2 * M_PI;
    while (angle >= 2 * M_PI) 
		angle -= 2 * M_PI;
    return angle;
}

bool	keyboard_roations(t_game *game)
{
	bool moved;

	moved = false;
	if (mlx_is_key_down(game->mlx, MLX_KEY_RIGHT))
	{
		if (DEBUG)
			printf(BLUE"%15s:"YELLOW"%-3d:"RESET"%-15s:    "BBLUE"\t%4s\t"RESET"\n", __FILE__, __LINE__, __FUNCTION__, "ROTATE RIGHT");
		game->player->radian += 0.05;
		toggle_bool(&moved);
	}
	else if (mlx_is_key_down(game->mlx, MLX_KEY_LEFT))
	{
		if (DEBUG)
			printf(BLUE"%15s:"YELLOW"%-3d:"RESET"%-15s:    "BBLUE"\t%4s\t"RESET"\n", __FILE__, __LINE__, __FUNCTION__, "ROTATE LEFT");
		game->player->radian -= 0.05;
		toggle_bool(&moved);
	}
	return (moved);
}

bool	mouse_rotations(t_game *game, int32_t old_mouse_x, int32_t old_mouse_y)
{
	bool	moved;
	int32_t new_mouse_x;
	int32_t new_mouse_y;
	int32_t	delta_mouse_x;

	(void) old_mouse_y;
	(void) new_mouse_y;
	moved = false;
	mlx_get_mouse_pos(game->mlx, &new_mouse_x, &new_mouse_y);
	delta_mouse_x = new_mouse_x - old_mouse_x;
	if (delta_mouse_x >= MOUSE_MOUVEMENT_DETECTION_THRESHOLD || delta_mouse_x <= -MOUSE_MOUVEMENT_DETECTION_THRESHOLD)
	{
		if (DEBUG)
		{
			print_debug_prefix(WHERE_FUNC, "MOUSE ROTATE");
			print_player_infos(game->player, "before");
		}
		game->player->radian += delta_mouse_x * MOUSE_SENSITIVITY;
		moved = true;
	}
	return (moved);
}

void	ft_keys_mouse_player_rotations(t_game *game, int32_t old_mouse_x, int32_t old_mouse_y)
{

	bool	did_rotate;

	did_rotate = false;
	did_rotate = keyboard_roations(game);
	did_rotate |= mouse_rotations(game, old_mouse_x, old_mouse_y);
	if (did_rotate)
	{
		game->player->radian = normalize_angle(game->player->radian);
		update_player_direction(game->player);
		if (DEBUG)
			print_player_infos(game->player, "rotated");
	}
}
