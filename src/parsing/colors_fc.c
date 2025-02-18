#include "cub.h"

int	check_fc(t_mm *mm, t_parsing_map *map)
{
	char	*tmp;

	if (ft_isdigit(map->color_ceiling[2]) || ft_isdigit(map->color_floor[2]))
		mm_nuclear_exit(mm, ft_error(WHERE, "The ceiling or floor isn't valid", EXIT_FAILURE));
	tmp = safe_strdup(mm, ZONE_1, map->color_ceiling);
	safe_free(mm, ZONE_1, map->color_ceiling);
	if (update_color(mm, &map->color_ceiling, tmp) == EXIT_FAILURE)
		mm_nuclear_exit(mm, ft_error(WHERE, "The ceiling isn't valid", EXIT_FAILURE));
	tmp = safe_strdup(mm, ZONE_1, map->color_floor);
	safe_free(mm, ZONE_1, map->color_floor);
	if (update_color(mm, &map->color_floor, tmp) == EXIT_FAILURE)
		mm_nuclear_exit(mm, ft_error(WHERE, "The floor isn't valid", EXIT_FAILURE));
	return (EXIT_SUCCESS);
}

int	validate_color_format(char *color)
{
	int	i;

	i = 0;
	while (color[i])
	{
		if ((color[i] != ',') && (is_white_space(color[i]) == 0 || \
		ft_isdigit(color[i])))
			return (EXIT_FAILURE);
		i++;
	}
	return (EXIT_SUCCESS);
}

int	check_format_fc(t_mm *mm,t_parsing_map *map)
{
	if (validate_color_format(map->color_ceiling) == EXIT_FAILURE)
		mm_nuclear_exit(mm, ft_error(WHERE, "The ceiling isn't valid", EXIT_FAILURE));
	if (validate_color_format(map->color_floor) == EXIT_FAILURE)
		mm_nuclear_exit(mm, ft_error(WHERE, "The floor isn't valid", EXIT_FAILURE));
	return (EXIT_SUCCESS);
}

int	validate_color_range(t_mm *mm, char *color)
{
	char	**splited;
	int		i;
	int		tmp;

	splited = ft_split(color, ',');
	i = 0;
	while (splited[i])
	{
		tmp = ft_atoi(splited[i]);
		if (tmp < 0 || tmp > 255)
		{
			free_tab(mm, splited);
			printf("Error : Format not valid\n");
			return (EXIT_FAILURE);
		}
		i++;
	}
	free_tab(mm, splited);
	return (EXIT_SUCCESS);
}

int	verif_colors(t_mm *mm, t_parsing_map *map)
{
	if (validate_color_range(mm, map->color_ceiling) == EXIT_FAILURE)
		mm_nuclear_exit(mm, ft_error(WHERE, "Format not valid", EXIT_FAILURE));
	if (validate_color_range(mm, map->color_floor) == EXIT_FAILURE)
		mm_nuclear_exit(mm, ft_error(WHERE, "Format not valid", EXIT_FAILURE));
	return (EXIT_SUCCESS);
}
