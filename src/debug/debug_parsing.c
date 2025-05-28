
#include "cub.h"

void	debug_parsing_player_pos(t_game *game, int i ,int j)
{
	(void) game;
	print_debug_prefix(WHERE_FUNC, "");
	printf("player position:\t"RED" x: %-4d" \
								GREEN" y: %-4d"RESET"\n", j, i);
}


void	debug_map_extraction(t_map *map)
{
	int	y;
	int	x;

	print_debug_prefix(WHERE_FUNC, "Debug map extraction\n\n");
	y = -1;
	while (++y <= map->y_max - 1)
	{
		x = -1;
		while (++x <= map->x_max - 1)
		{
			if (map->grid[y][x] == '\0')
				printf(BGBLUE"\\0"RESET);
			else if (map->grid[y][x] == '1')
				printf(BGWHITE" 1"RESET);
			else if (map->grid[y][x] == '0')
				printf(BGYELLOW" 0"RESET);
			else if (map->grid[y][x] == 'N' || map->grid[y][x] == 'S' \
					|| map->grid[y][x] == 'E' ||map->grid[y][x] == 'W' )
				printf(BGRED" P"RESET);
			else
				printf(BGBLACK" %c"RESET, map->grid[y][x]);
		}
		printf(BGBBLUE"\\0"RESET"\n");
	}
	printf("\n");
}
