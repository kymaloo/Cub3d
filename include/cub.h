#ifndef CUB_H
# define CUB_H

# include <stdio.h>
# include <fcntl.h>
# include <stdbool.h>
# include "define.h"
# include "struct.h"
# include "../libft/libft.h"
# include "memory_manager.h"
# include "ft_error.h"
# include "MLX42/MLX42.h"

int		init(t_game *game, char *str);
void	line_size(t_game *game, char *str, int fd);
void	count_line(t_game *game, char *str, int fd);
void	init_mlx(t_game *game);

#endif