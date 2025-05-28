/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekrebs <ekrebs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 09:34:46 by ekrebs            #+#    #+#             */
/*   Updated: 2025/05/28 21:02:11 by ekrebs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEBUG_H
# define DEBUG_H
# include "cub.h"

# ifndef CAPTURE_MOUSE_ON_STARTUP
#  define CAPTURE_MOUSE_ON_STARTUP true
# endif
# ifndef DEBUG_KEYS
#  define DEBUG_KEYS false
# endif
# ifndef DEBUG_MOUSE
#  define DEBUG_MOUSE false
# endif
# ifndef DEBUG_EXTRACT
#  define DEBUG_EXTRACT false
# endif
# ifndef RESOLUTION_NB_KS
#  define RESOLUTION_NB_KS 2
# endif
# ifndef DEBUG
#  define DEBUG	false
# endif

# if RESOLUTION_NB_KS == 4
#  define WIDTH				3840
#  define HEIGHT			2160
# elif RESOLUTION_NB_KS == 2
#  define WIDTH				1920
#  define HEIGHT			1080
# elif RESOLUTION_NB_KS == 666
#  define WIDTH				400
#  define HEIGHT			300
# else
#  define WIDTH				1280
#  define HEIGHT			720
# endif

# define WHERE_FUNC __FILE__, __LINE__, __FUNCTION__

//generals
void	print_debug_prefix(char *file, int line, \
											const char *func, char *str_msg);
void	print_player_infos(t_player *player, char *str_prefix);
void	print_coord(char *str_prefix, char *str_suffix, float x, float y);
void	print_map_around(t_game *g, int x, int y, int offset);
void	print_map_player(t_game *g, int offset);

//specifics:
//main.c
void	debug_main_prefix(char *name);
void	debug_main_post_parsing(t_game *game);
void	debug_main_suffix(t_game *game, char *name);

//parsing
void	debug_parsing_player_pos(t_game *game, int i, int j);
void	debug_map_extraction(t_map *map);
#endif