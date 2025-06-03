#ifndef STRUCT_H
# define STRUCT_H

# include "memory_manager.h"

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

typedef struct s_ray
{
	double	dir_x;
	double	dir_y;
	double	side_dist_x;
	double	side_dist_y;
	double	delta_dist_x;
	double	delta_dist_y;
	int		map_x;
	int		map_y;
	int		step_x;
	int		step_y;
	int		hit;
	int		side; // 0 = x, 1 = y
	int		draw_end;
	int		draw_start;
	double realdist;
	double perp_wall_dist;
	int line_height;
	mlx_texture_t *current_texture;
	uint8_t *pixel;
	uint32_t color;
	double wall_hit_x;  // Exact X hit position
    double wall_hit_y;
}	t_ray;

typedef	struct s_colors
{
	char	*color_floor;
	char	*color_ceiling;
	int		floor;
	int		ceiling;
}	t_colors;

typedef	struct s_path
{
	char	*north;
	char	*south;
	char	*east;
	char	*west;
}	t_path;

typedef	struct s_map
{
	char	**grid;
	int		x_max;
	int		y_max;
	int		tile_size;
}	t_map;

typedef	struct s_image
{
	mlx_image_t			*img_window;
	mlx_image_t			*player_img;
	mlx_image_t			*minimap;
}	t_image;

typedef	struct s_texture
{
	mlx_texture_t *north;
    mlx_texture_t *south;
    mlx_texture_t *east;
    mlx_texture_t *west;
	mlx_texture_t	*player;
	t_image			*image;
}	t_texture;


typedef struct s_player
{
	double	position[DIM];
	char	facing;
	double	direction[DIM];
	double	radian;
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
}			t_game;

typedef struct s_data
{
	t_parsing_map	*parse;
	t_game			*game;
	t_colors		*colors;
	t_path			*path;
} t_data;

#endif