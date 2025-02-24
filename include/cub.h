#ifndef CUB_H
# define CUB_H

# include <stdio.h>
# include <fcntl.h>
# include <stdbool.h>
# include <math.h>
# include "define.h"
# include "struct.h"
# include "../libft/libft.h"
# include "memory_manager.h"
# include "ft_error.h"
# include "MLX42/MLX42.h"

int	init(t_infos_p *infos_p, char *str);
void draw_map(t_game *g);
void ft_hook(void *gamed);
void print_minimap(t_game *g);
void	ft_move_perso(t_game *g);
int	ft_check_collision_top(t_game *g);
int	ft_check_collision_bot(t_game *g);
int	ft_check_collision_left(t_game *g);
int	ft_check_collision_right(t_game *g);
void	create_memory_manager(t_infos_p **infos_p);
void	stock_radian(t_player *player);

#endif