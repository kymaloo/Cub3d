/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   define.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekrebs <ekrebs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 09:24:42 by ekrebs            #+#    #+#             */
/*   Updated: 2025/05/28 16:06:41 by ekrebs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINE_H
# define DEFINE_H

# define MALLOC_FAILED		"Error: Malloc failed\n"

# define ZONE_PARSE				"petit_chacalot"
# define ZONE_MLX			"zebi_la_mlx"
# define ZONE_FDS			"oulah_les_Fds"

# ifdef M_PI
#  undef M_PI
# endif
# ifdef M_2_PI
#  undef M_2_PI
# endif
# define M_PI				3.1415
# define M_2_PI				6.2831
# define M_3_PI				9.4247
# define M_5_PI				15.7079
# define M_7_PI				21.9911
# define M_PI_BY_8			0.39269

# define C_WALL_BLACK		0xFFFFFFFF
# define C_FLOOR_BROWN		0x4B3A26FF
# define C_BLUE				0x0000FFFF
# define C_WHITE			0xFFFFFFFF
# define C_GREY_INVALID		0xD3D3D3FF
# define C_RED				0xFF0000FF
# define C_GREEN			0x00FF00FF
# define C_YELLOW			0xFFFF00FF

# define TILE_SIZE			64
# define DETECTION_RANGE 	10
# define PLAYER_ADJUSTMENT	5

# define TILE_SIZE_MINIMAP	16

# define MOUSE_SENSITIVITY 0.002
# define MOUSE_MOUVEMENT_DETECTION_THRESHOLD 5

# define DIM	2

# define FOV	 70
# define FOV_DEG 0.6108// FOV * M_PI / 360.0

# define MOVE_SPEED 0.3
# define PLAYER_WIDTH 0.05

enum e_coord
{
	X = 0,
	Y = 1,
};

enum e_error
{
	MALLOC_ERROR = -1,
	EXIT_SUCCESS,
	EXIT_FAILURE,
	DIRECTION,
	FC,
};

#endif