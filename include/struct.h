/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekrebs <ekrebs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 09:37:14 by ekrebs            #+#    #+#             */
/*   Updated: 2025/06/18 01:42:14 by ekrebs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

# include "memory_manager.h"

struct s_safe_split_data
{
	int			nbword;
	char		**tab;
	const char	*start;
	int			i;
};

typedef struct s_parsing_map
{
	char	**grid;
	char	**grid_copy;
	char	**all_file;
	char	**direction;
	char	**fc;
	char	*color_floor_cp;
	char	*color_ceiling_cp;
	int		x_last_0;
	int		y_last_0;
}	t_parsing_map;

/**
 * float side; // 0 = x, 1 = y
 * int wall_hit_x; // Exact X hit position
 * 
 */
typedef struct s_ray
{
	float			dir_x;
	float			dir_y;
	float			side_dist_x;
	float			side_dist_y;
	float			delta_dist_x;
	float			delta_dist_y;
	int				map_x;
	int				map_y;
	int				step_x;
	int				step_y;
	int				hit;
	int				side;
	int				draw_end;
	int				draw_start;
	float			realdist;
	float			perp_wall_dist;
	int				line_height;
	mlx_texture_t	*current_texture;
	uint8_t			*pixel;
	uint32_t		color;
	float			wall_hit_x;
	float			wall_hit_y;
}	t_ray;

typedef struct s_colors
{
	char		*color_floor;
	char		*color_ceiling;
	int			floor;
	int			ceiling;
	uint32_t	color_floor_uint;
	uint32_t	color_ceiling_uint;
}	t_colors;

typedef struct s_path
{
	char	*north;
	char	*south;
	char	*east;
	char	*west;
}	t_path;

typedef struct s_map
{
	char	**grid;
	int		x_max;
	int		y_max;
	int		tile_size;
}	t_map;

typedef struct s_image
{
	mlx_image_t			*img_window;
	mlx_image_t			*player_img;
	mlx_image_t			*minimap;
}	t_image;

typedef struct s_texture
{
	mlx_texture_t	*north;
	mlx_texture_t	*south;
	mlx_texture_t	*east;
	mlx_texture_t	*west;
	mlx_texture_t	*player;
	t_image			*image;
}	t_texture;

typedef struct s_player
{
	float	position[DIM];
	char	facing;
	float	direction[DIM];
	float	radian;
}	t_player;

typedef struct s_toggles
{
	bool	catch_mouse_cursor;
	bool	minimap;
}	t_toggles;

typedef struct s_game
{
	t_texture			*texture;
	t_player			*player;
	t_map				*map;
	mlx_t				*mlx;
	int					colors_minimap;
	t_ray				*ray;
	t_toggles			toggles;
	t_path				*path;
	t_colors			*colors;
}			t_game;

typedef struct s_data
{
	t_parsing_map	*parse;
	t_game			*game;
	t_colors		*colors;
	t_path			*path;
}	t_data;

#endif