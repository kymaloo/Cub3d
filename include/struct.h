#ifndef STRUCT_H
# define STRUCT_H

# include "memory_manager.h"
# include "engine_3d.h"

# define GRID_X 64
# define GRID_Y 64

typedef struct s_parsing_map
{
	char	**grid;
	char	**grid_copy;
	char	**all_file;
	char	**direction;
	char	**fc;
	char	*path_north;
	char	*path_south;
	char	*path_east;
	char	*path_west;
	char	*color_floor;
	char	*color_ceiling;
	char	*color_floor_cp;
	char	*color_ceiling_cp;
	int		x_last_0;
	int		y_last_0;
}	t_parsing_map;

typedef	struct s_textures
{
	char	*path_north;
	char	*path_south;
	char	*path_east;
	char	*path_west;
	char	*color_floor;
	char	*color_ceiling;
}	t_textures;

typedef	struct s_map
{
	char	**map;
	int		x_max;
	int		y_max;
}	t_map;

typedef	struct s_time
{
	double	now;
	double	old;
	double	taken_to_draw_frame;
}	t_time;



typedef struct s_game
{
	t_memory_manager	*mm;
	mlx_t				*mlx;
	t_player			player;
	t_map				map;
	t_textures			textures;
	t_time				time;
}			t_game;

#endif