#include "../include/cub.h"

int	main(int argc, char **argv)
{
	t_parsing_map	*map;

	if (argc != 2)
	{
		printf("Error: Wrong argument\n");
		return (1);
	}
	map = ft_calloc(1, sizeof(t_parsing_map));
	init_tab_direction(map);
	init_tab_fc(map);
	init_direction(map, argv[1], 0, 0);
	init_fc(map, argv[1]);
	ft_count_line(map, argv[1], 0);
	line_size(map, argv[1], 0);
	return (0);
}
