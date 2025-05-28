/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_interns.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekrebs <ekrebs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 15:08:50 by trgaspar          #+#    #+#             */
/*   Updated: 2025/05/28 09:45:51 by ekrebs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_INTERNS_H
# define PARSING_INTERNS_H

# include "memory_manager.h"
# include "struct.h"

int		check_map_format_cub(char *str);
int		check_white_space(char *str);
int		strncmp_with_array(char *str, char **array, size_t n);
int		init_tab_direction(t_parsing_map *p);
int		init_tab_fc(t_parsing_map *p);
int		open_map(char *str);
int		close_map(int fd);
int		init_direction(t_data *data, char *str, int dir, int fd);
int		process_direction(t_data *data, char *line, int dir_i, int fd);
int		init_fc(t_data *data, char *str);
void	print_map(char **map);
int		count_line_in_file(char *str);
int		check_map(char **map);
char	**stock_file(char *str);
char	**extract_map(t_data *data, char **array);
void	copy_map(t_data *data);
int		is_white_space(char c);
int		check_wall(t_data *data);
int		check_doublon_map(char **map, char *str);
int		check_fc(t_data *data);
int		verif_colors(t_colors *colors);
int		check_format_fc(t_colors *colors);
int		validate_color_range(char *color);
int		validate_color_format(char *color);
int		update_color(char **color, char *tmp);
int		check_map_reel(char *str);
int		count_dir_in_file(t_parsing_map *p, char **dir);
int		count_fc_in_file(t_parsing_map *p, char **dir);
int		char_valid_for_map(char *cmp, char *str);
int		all_line_is_valid(t_data *data, char **array);
int		get_size_of_array(t_data *data, char **t, int i);
int		get_index_before_array(t_data *data, char **array, int i);
void	get_line_size(t_data *data, char **array);
void	find_pos_player(t_game *game, char **grid);
int		check_line_map(t_map *map);
void	char_to_rgb(t_colors *colors, char *str, int id);

#endif