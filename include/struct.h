#ifndef STRUCT_H
# define STRUCT_H

# include "memory_manager.h"
# include "engine_3d.h"

# define GRID_SIZE_X	32
# define GRID_SIZE_Y	32


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

typedef	struct s_mlx_texture
{
	mlx_texture_t	*player;
}	t_mlx_texture;

typedef	struct s_image
{
	mlx_image_t			*img_window;
	mlx_image_t			*player_img;
	mlx_image_t			*minimap;
}	t_image;

typedef	struct s_colors
{
	char	*color_floor;
	char	*color_ceiling;
}	t_colors;

typedef	struct s_path
{
	char	*north;
	char	*south;
	char	*east;
	char	*west;
}	t_path;

typedef	struct s_texture
{
	mlx_texture_t	*player;
	t_image			*image;
	t_colors		*colors;
	t_path			*path;
}	t_texture;

typedef	struct s_map
{
	char	**map;
	int		x_max;
	int		y_max;
	int		tile_size;
}	t_map;

typedef struct s_player
{
	char		facing;
	double		position[NB_DIM];
	t_camera	camera;
	double		angle;
}	t_player;

typedef	struct s_time
{
	struct timeval	now;
	struct timeval	old;
	suseconds_t	time_taken_to_draw_frame;
}	t_time;

typedef struct s_game
{
	int					color;
	mlx_t				*mlx;
	t_player			*player;
	t_map				*map;
	t_texture			*texture;
	t_time				*time;
}			t_game;

typedef struct s_infos_p
{
	t_parsing_map	*p;
	t_game			*g;
} t_infos_p;

#endif