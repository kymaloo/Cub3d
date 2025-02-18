#include "cub.h"
#include "parsing_interns.h"

void	free_tab(t_mm *mm, char **tab)
{
	int	i;

	i = 0;
	while (tab[i] != NULL)
	{
		safe_free(mm, ZONE_1, tab[i]);
		i++;
	}
	safe_free(mm, ZONE_1, tab);
}

void	free_all(t_mm *mm, t_parsing_map *map)
{
	if (map->direction != NULL)
		free_tab(mm, map->direction);
	if (map->fc != NULL)
		free_tab(mm, map->fc);
	if (map->grid_and_dir != NULL)
		free_tab(mm, map->grid_and_dir);
	if (map->path_east != NULL)
		safe_free(mm, ZONE_1, map->path_east);
	if (map->path_west != NULL)
		safe_free(mm, ZONE_1, map->path_west);
	if (map->path_south != NULL)
		safe_free(mm, ZONE_1, map->path_south);
	if (map->path_north != NULL)
		safe_free(mm, ZONE_1, map->path_north);
	if (map->color_ceiling != NULL)
		safe_free(mm, ZONE_1, map->color_ceiling);
	if (map->color_floor != NULL)
		safe_free(mm, ZONE_1, map->color_floor);
	if (map->grid != NULL)
		free_tab(mm, map->grid);
	if (map->grid_copy != NULL)
		free_tab(mm, map->grid_copy);
	if (map != NULL)
		safe_free(mm, ZONE_1, map);
}
