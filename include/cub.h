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
# include "MLX42/MLX42_Int.h"
# include "dda.h"

int		init(t_data *data, char *str);
void	draw_map(t_game *g);
void	ft_hook(void *gamed);
void	print_minimap(t_game *g);
void	ft_move_perso(t_game *g);
void	create_memory_manager(t_data **data);
void	stock_radian(t_player *player);
bool	isset(char c, char *set);
void	print_map(char **map);
int		is_wall(t_map *map, int x, int y);
void	ft_move_perso(t_game *g);


void	raycast(t_game *game);
void	perform_dda(t_ray *ray, char **grid);
//void	init_ray(t_ray *ray, t_player *player, double ray_angle);

#endif