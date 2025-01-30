#ifndef CUB_H
# define CUB_H

# include <stdio.h>
# include <fcntl.h>
# include "define.h"
# include "struct.h"
# include "../libft/libft.h"

int		ft_check_map_format_cub(char *str);
char	**extract_map(t_parsing_map *map, char *str);
int		check_white_space(char *str);
int		strncmp_with_array(char *str, char **array, size_t n);
int		init_tab_direction(t_parsing_map *map);
int		init_tab_fc(t_parsing_map *map);
int		open_map(char *str);
int		close_map(int fd);
int		count_dir(t_parsing_map *map, char *str, int count, int fd);
int		count_fc(t_parsing_map *map, char *str, int count, int fd);
int		get_index_before_map(t_parsing_map *map, char *str, int count, int fd);
int		init_direction(t_parsing_map *map, char *str, int dir, int fd);
int		process_direction(t_parsing_map *map, char *line, int dir_index, int fd);
int		check_doublon(char *direction, char *line, int fd);
void	save_path(t_parsing_map *map, char *line, int dir_index);
int		init_fc(t_parsing_map *map, char *str);
void	line_size(t_parsing_map *map, char *str, int fd);
void	ft_count_line(t_parsing_map *map, char *str, int fd);

#endif