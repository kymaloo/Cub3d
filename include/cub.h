#ifndef CUB_H
# define CUB_H

# include <stdio.h>
# include <fcntl.h>
# include <stdbool.h>
# include "define.h"
# include "struct.h"
# include "../libft/libft.h"

int		check_map_format_cub(char *str);
int		check_white_space(char *str);
int		strncmp_with_array(char *str, char **array, size_t n);
int		init_tab_direction(t_parsing_map *map);
int		init_tab_fc(t_parsing_map *map);
int		open_map(char *str);
int		close_map(int fd);
int		count_dir(char **dir, char *str, int count, int fd);
int		count_fc(char **fc, char *str, int count, int fd);
int		get_index_before_map(t_parsing_map *map, char *str, int count, int fd);
int		init_direction(t_parsing_map *map, char *str, int dir, int fd);
int		process_direction(t_parsing_map *map, char *line, int dir_i, int fd);
int		check_doublon(char *direction, char *line, int fd);
int		init_fc(t_parsing_map *map, char *str);
void	line_size(t_parsing_map *map, char *str, int fd);
void	count_line(t_parsing_map *map, char *str, int fd);
void	print_map(char **map);
int		count_line_in_file(char *str);
int		check_map(char **map);
char	**stock_file(char *str);
char	**extract_map(t_parsing_map *map, char **src, char *str);
void	free_tab(char **tab);
int		init(t_parsing_map *map, char *str);
void	copy_map(t_parsing_map *map);
int		is_white_space(char c);
int		check_wall(t_parsing_map *map);
int		init(t_parsing_map *map, char *str);
int		check_doublon_map(char **map, char *str);
int		check_fc(t_parsing_map *map);
int		verif_colors(t_parsing_map *map);
int		check_format_fc(t_parsing_map *map);
int		validate_color_range(char *color);
int		validate_color_format(char *color);
int		update_color(char **color, char *tmp);
void	free_all(t_parsing_map *map);
int		check_map_reel(char *str);
#endif