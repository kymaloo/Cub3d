/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekrebs <ekrebs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 09:34:46 by ekrebs            #+#    #+#             */
/*   Updated: 2025/05/28 11:41:12 by ekrebs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEBUG_H
# define DEBUG_H
# include "cub.h"

# ifndef DEBUG_KEYS
#  define DEBUG_KEYS false
# endif
# ifndef DEBUG_MOUSE
#  define DEBUG_MOUSE false
# endif
# ifndef DEBUG_EXTRACT
#  define DEBUG_EXTRACT false
# endif
# ifndef DEBUG_DDA
#  define DEBUG_DDA false
# endif
# ifndef RESOLUTION_NB_KS
#  define RESOLUTION_NB_KS 1
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
# else
#  define WIDTH				1280
#  define HEIGHT			720
# endif

# define WHERE_FUNC __FILE__, __LINE__, __FUNCTION__

void	print_debug_prefix(char *file, int line, \
											const char *func, char *str_msg);
void	print_player_infos(t_player *player, char *str_prefix);
void	print_coord(char *str_prefix, char *str_suffix, float x, float y);
void	print_map_around(t_game *g, int x, int y, int offset);
void	print_map_player(t_game *g, int offset);

#endif