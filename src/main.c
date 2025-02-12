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
	init(map, argv[1]);

	count_line(map, argv[1], 0);
	line_size(map, argv[1], 0);
	map->grid_and_dir = stock_file(argv[1]);
	map->grid = extract_map(map, map->grid_and_dir, argv[1]);
	copy_map(map);
	print_map(map->grid);
	//print_map(map->grid_copy);
	find_last_floor(map);
	//if (path_finding(1, 9, map->grid_copy) == 0)
		//puts("let's goooo");

	free_tab(map->direction);
	free_tab(map->fc);
	free_tab(map->grid_and_dir);
	free(map->path_east);
	free(map->path_west);
	free(map->path_south);
	free(map->path_north);
	free(map->color_ceiling);
	free(map->color_floor);
	free_tab(map->grid);
	free_tab(map->grid_copy);
	free(map);
	return (0);
}
