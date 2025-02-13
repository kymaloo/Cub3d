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
	free_all(map);
	return (0);
}
