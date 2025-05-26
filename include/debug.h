

#ifndef DEBUG_H
# define DEBUG_H
#include "cub.h"

#ifndef DEBUG_KEYS
# define DEBUG_KEYS false
#endif

#ifndef DEBUG_MOUSE
# define DEBUG_MOUSE false
#endif

#define WHERE_FUNC __FILE__, __LINE__, __FUNCTION__

void	print_debug_prefix(char *file, int line, const char *func, char *str_msg);
void	print_player_infos(t_player* player, char *str_prefix);
void	print_coord(char *str_prefix, char *str_suffix, float x, float y);
void	print_map_around(t_game *g, int x, int y, int offset);
void	print_map_player(t_game *g, int offset);

#endif

