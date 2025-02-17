#include "cub.h"

void	free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i] != NULL)
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

void	free_all(t_parsing_map *map)
{
	if (map->direction != NULL)
		free_tab(map->direction);
	if (map->fc != NULL)
		free_tab(map->fc);
	if (map->grid_and_dir != NULL)
		free_tab(map->grid_and_dir);
	if (map->path_east != NULL)
		free(map->path_east);
	if (map->path_west != NULL)
		free(map->path_west);
	if (map->path_south != NULL)
		free(map->path_south);
	if (map->path_north != NULL)
		free(map->path_north);
	if (map->color_ceiling != NULL)
		free(map->color_ceiling);
	if (map->color_floor != NULL)
		free(map->color_floor);
	if (map->grid != NULL)
		free_tab(map->grid);
	if (map->grid_copy != NULL)
		free_tab(map->grid_copy);
	if (map != NULL)
		free(map);
}
