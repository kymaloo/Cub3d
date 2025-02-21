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

typedef struct s_game
{
	t_mm			*mm;
	t_parsing_map 	*parse;
}			t_game;

#endif