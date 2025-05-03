
#ifndef CUB_H
# define CUB_H

# include <stdio.h>
# include <fcntl.h>
# include <stdbool.h>
# include <math.h>
# include <sys/time.h>
# include "memory_manager.h"
# include "define.h"
# include "struct.h"
# include "../libft/libft.h"
# include "ft_error.h"
# include "MLX42/MLX42.h"
# include "radar.h"
# include "engine_3d.h"
# include "game_loop.h"

# ifdef DEBUG
#  if DEBUG == EXPLOSIVES
#   include "explosives.h"
#  endif
# endif

int		parse_map_init_game_infos(t_game *infos_p, char *str);
void	draw_map(t_game *g);
void	ft_hook(void *gamed);
void	print_minimap(t_game *g);
void	ft_move_perso(t_game *g);
void	create_memory_manager();
void	stock_radian(t_player *player);
bool	isset(char c, char *set);
void	print_map(char **map);
int		is_wall(char **map, int x, int y);

#endif