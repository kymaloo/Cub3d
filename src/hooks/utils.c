#include "cub.h"

float normalize_angle(float angle) 
{
    while (angle < 0)
		angle += 2 * M_PI;
    while (angle >= 2 * M_PI) 
		angle -= 2 * M_PI;
    return angle;
}

void	update_player_direction(t_player *player)
{
	player->direction[0] = cos(player->radian); // X component
	player->direction[1] = sin(player->radian); // Y component
}

