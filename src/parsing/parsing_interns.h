/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_interns.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trgaspar <trgaspar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 15:08:50 by trgaspar          #+#    #+#             */
/*   Updated: 2025/02/21 16:06:45 by trgaspar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_INTERNS_H
# define PARSING_INTERNS_H

# include "memory_manager.h"
# include "struct.h"

int     check_map_format_cub(t_game *game, char *str);
int		check_white_space(char *str);
int		strncmp_with_array(char *str, char **array, size_t n);
int		init_tab_direction(t_mm *mm, t_parsing_map *parse);
int		init_tab_fc(t_mm *mm, t_parsing_map *parse);
int		init_tab_direction(t_mm *mm, t_parsing_map *parse);
int		init_tab_fc(t_mm *mm, t_parsing_map *parse);
int		open_map(char *str);
int		close_map(int fd);
int		init_direction(t_game *game, char *str, int dir, int fd);
int		process_direction(t_game *game, char *line, int dir_i, int fd);
int		init_fc(t_game *game, char *str);
void	print_map(char **map);
int		count_line_in_file(t_mm *mm, char *str);
int		check_map(char **map);
char	**stock_file(t_mm *mm, char *str);
char	**extract_map(t_game *game, char **array);
void	copy_map(t_game *game);
int		is_white_space(char c);
int		check_wall(t_mm *mm, t_parsing_map *parse);
int		check_wall(t_mm *mm, t_parsing_map *parse);
int		check_doublon_map(char **map, char *str);
int		check_fc(t_game *game);
int		verif_colors(t_game *game);
int		check_format_fc(t_mm *mm, t_parsing_map *parse);
int		validate_color_range(t_mm *mm, char *color);
int		validate_color_format(char *color);
int		update_color(t_game *game, char **color, char *tmp);
int		check_map_reel(t_mm *mm, char *str);
int		count_dir_in_file(t_game *game, char **dir);
int		count_fc_in_file(t_game *game, char **dir);
int		char_valid_for_map(char *cmp, char *str);
int		all_line_is_valid(t_game *game, char **array);
int		get_size_of_array(t_game *game, char **array, int i);
int		get_index_before_array(t_game *game, char **array);
int		get_line_size(t_game *game, char **array);

#endif