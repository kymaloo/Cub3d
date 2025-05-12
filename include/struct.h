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

typedef struct s_player
{
	double	position[DIM];
	char	facing;
	double	direction[DIM];
	double	radian;
}	t_player;

typedef struct s_game
{
	t_player			*player;
	t_map				*map;
}			t_game;

typedef struct s_data
{
	t_parsing_map	*parse;
	t_game			*game;
	t_colors		*colors;
	t_path			*path;
} t_data;

#endif