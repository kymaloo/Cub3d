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
	char	*path_north;		//fill me
	char	*path_south;		//fill me
	char	*path_east;			//fill me
	char	*path_west;			//fill me
	char	*color_floor;		//fill me
	char	*color_ceiling;		//fill me
}	t_textures;

typedef	struct s_map
{
	char	**map; //fill me
	int		x_max; //fill me
	int		y_max; //fill me
}	t_map;

typedef struct s_player
{
	double	position[DIM];	//fill me
	char	facing;			//fill me (N S E ou W)
	double	direction[DIM];
	double	plane[DIM];
}	t_player;

typedef	struct s_time
{
	double	now;
	double	old;
	double	taken_to_draw_frame;
}	t_time;

typedef struct s_game
{
	mlx_t				*mlx;
	t_player			player;
	t_map				map;
	t_textures			textures;
	t_time				time;
}			t_game;

typedef struct s_infos_p
{
	t_parsing_map	*p;
	t_game			*g;
} t_infos_p;


#endif