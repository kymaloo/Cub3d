#ifndef STRUCT_H
# define STRUCT_H

# include "memory_manager.h"
# include "engine_3d.h"
# include "parsing.h"

# define GRID_SIZE_X	32
# define GRID_SIZE_Y	32

typedef	struct s_time
{
	struct timeval	now;
	struct timeval	old;
	suseconds_t		time_taken_to_draw_frame;
}	t_time;

typedef struct s_images
{
	mlx_image_t	*next_frame;
	mlx_image_t	*minimap;
	mlx_image_t	*minimap_player;
	mlx_image_t	*radar;
} t_images;

typedef	struct s_colors
{
	char	*color_floor;
	char	*color_ceiling;
}	t_colors;

typedef struct s_textures
{
	mlx_texture_t	*minimap_player;
	mlx_texture_t	*wall_north;
	mlx_texture_t	*wall_south;
	mlx_texture_t	*wall_east;
	mlx_texture_t	*wall_west;
} t_textures;

typedef struct s_paths
{
	char	*minimap_player;
	char	*wall_north;
	char	*wall_south;
	char	*wall_east;
	char	*wall_west;
} t_paths;

typedef struct s_mlx_infos
{
	mlx_t			*mlx;
	t_images		images;
	t_textures		textures;
	t_colors		colors;
	t_paths			paths;
} t_mlx_infos;

typedef	struct s_map
{
	char	**map;
	int		x_max;
	int		y_max;
	int		tile_size;
}	t_map;

typedef struct s_game
{
	t_player	player;
	t_map		map;
	t_mlx_infos	mlx_infos;
	t_time		time;
} t_game;

typedef struct s_infos_p
{
	t_parsing_map	*p;
	t_game			*g;
} t_infos_p;

#endif