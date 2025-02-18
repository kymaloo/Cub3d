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

void	free_all(t_mm *mm, t_parsing_map *parse)
{
	if (parse->direction != NULL)
		free_tab(mm, parse->direction);
	if (parse->fc != NULL)
		free_tab(mm, parse->fc);
	if (parse->grid_and_dir != NULL)
		free_tab(mm, parse->grid_and_dir);
	if (parse->path_east != NULL)
		safe_free(mm, ZONE_1, parse->path_east);
	if (parse->path_west != NULL)
		safe_free(mm, ZONE_1, parse->path_west);
	if (parse->path_south != NULL)
		safe_free(mm, ZONE_1, parse->path_south);
	if (parse->path_north != NULL)
		safe_free(mm, ZONE_1, parse->path_north);
	if (parse->color_ceiling != NULL)
		safe_free(mm, ZONE_1, parse->color_ceiling);
	if (parse->color_floor != NULL)
		safe_free(mm, ZONE_1, parse->color_floor);
	if (parse->grid != NULL)
		free_tab(mm, parse->grid);
	if (parse->grid_copy != NULL)
		free_tab(mm, parse->grid_copy);
	if (parse != NULL)
		safe_free(mm, ZONE_1, parse);
}
