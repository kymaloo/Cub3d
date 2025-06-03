#ifndef DDA_H
# define DDA_H

bool	is_within_map_boundaries(t_map *map, int x, int y);
void	update_player_direction(t_player *player);
float	normalize_angle(float angle);

#endif