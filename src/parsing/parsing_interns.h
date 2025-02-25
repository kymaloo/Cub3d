/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_interns.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trgaspar <trgaspar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 15:08:50 by trgaspar          #+#    #+#             */
/*   Updated: 2025/02/25 10:30:40 by trgaspar         ###   ########.fr       */
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
int		init_direction(t_infos_p *infos, char *str, int dir, int fd);
int		process_direction(t_infos_p *infos, char *line, int dir_i, int fd);
int		init_fc(t_infos_p *infos, char *str);
void	print_map(char **map);
int		count_line_in_file(char *str);
int		check_map(char **map);
char	**stock_file(char *str);
char	**extract_map(t_infos_p *infos, char **array);
void	copy_map(t_infos_p *infos);
int		is_white_space(char c);
int		check_wall(t_infos_p *infos_p);
int		check_doublon_map(char **map, char *str);
int		check_fc(t_texture *texture, t_parsing_map *p);
int		verif_colors(t_texture *texture);
int		check_format_fc(t_texture *texture);
int		validate_color_range(char *color);
int		validate_color_format(char *color);
int		update_color(char **color, char *tmp);
int		check_map_reel(char *str);
int		count_dir_in_file(t_parsing_map *p, char **dir);
int		count_fc_in_file(t_parsing_map *p, char **dir);
int		char_valid_for_map(char *cmp, char *str);
int		all_line_is_valid(t_texture *texture, char **array);
int		get_size_of_array(t_texture *texture, \
		t_parsing_map *p, char **t, int i);
int		get_index_before_array(t_infos_p *infos, char **array, int i);
void	get_line_size(t_infos_p *infos, char **array);
void	find_pos_player(t_game *game, char **grid);

#endif