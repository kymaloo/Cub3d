
#ifndef	PARSING_INTERNS_H
# define	PARSING_INTERNS_H

#include "memory_manager.h"
#include "struct.h"

int		check_map_format_cub(t_mm *mm, char *str);
int		check_white_space(char *str);
int		strncmp_with_array(char *str, char **array, size_t n);
int		init_tab_direction(t_mm *mm, t_parsing_map *map);
int		init_tab_fc(t_mm *mm, t_parsing_map *map);
int		open_map(char *str);
int		close_map(int fd);
int		count_dir(t_mm *mm, char **dir, char *str, int count, int fd);
int		count_fc(t_mm *mm, char **fc, char *str, int count, int fd);
int		get_index_before_map(t_mm *mm, t_parsing_map *map, char *str, int count, int fd);
int		init_direction(t_mm *mm, t_parsing_map *map, char *str, int dir, int fd);
int		process_direction(t_mm *mm, t_parsing_map *map, char *line, int dir_i, int fd);
int		check_doublon(t_mm *mm, char *direction, char *line, int fd);
int		init_fc(t_mm *mm, t_parsing_map *map, char *str);
void	print_map(char **map);
int		count_line_in_file(t_mm *mm, char *str);
int		check_map(char **map);
char	**stock_file(t_mm *mm, char *str);
char	**extract_map(t_mm *mm, t_parsing_map *map, char **src, char *str);
void	free_tab(t_mm *mm, char **tab);
void	copy_map(t_mm *mm, t_parsing_map *map);
int		is_white_space(char c);
int		check_wall(t_mm *mm, t_parsing_map *map);
int		check_doublon_map(char **map, char *str);
int		check_fc(t_mm *mm, t_parsing_map *map);
int		verif_colors(t_mm *mm, t_parsing_map *map);
int		check_format_fc(t_mm *mm, t_parsing_map *map);
int		validate_color_range(t_mm *mm, char *color);
int		validate_color_format(char *color);
int		update_color(t_mm *mm, char **color, char *tmp);
void	free_all(t_mm *mm, t_parsing_map *map);
int		check_map_reel(t_mm *mm, char *str);

#endif