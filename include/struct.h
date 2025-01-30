typedef struct s_parsing_map
{
	char	**grid;
	char	**grid_copy;
	char	**direction;
	char	**fc;
	char	*path_north;
	char	*path_south;
	char	*path_east;
	char	*path_west;
	char	*color_floor;
	char	*color_ceiling;
	int		count_line;
	int		line_size;
}	t_parsing_map;