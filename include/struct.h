typedef struct s_parsing_map
{
	char	**grid;
	char	**grid_copy;
	char	**grid_and_dir;
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
	int		x_last_0;
	int		y_last_0;
}	t_parsing_map;