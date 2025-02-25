
#include "cub.h"
#include "parsing_interns.h"

int	check_fc(t_texture *texture, t_parsing_map *p)
{
	char	*tmp;

	p->color_ceiling_cp = safe_strdup(ZONE_1, texture->colors->color_ceiling);
	p->color_floor_cp = safe_strdup(ZONE_1, texture->colors->color_floor);
	if (ft_isdigit(texture->colors->color_ceiling[2])
		|| ft_isdigit(texture->colors->color_floor[2]))
		nuclear_exit(ft_error(WHERE, \
		"The ceiling or floor isn't valid", EXIT_FAILURE));
	tmp = safe_strdup(ZONE_1, texture->colors->color_ceiling);
	safe_free(ZONE_1, texture->colors->color_ceiling);
	if (update_color(&texture->colors->color_ceiling, tmp) == EXIT_FAILURE)
		nuclear_exit(ft_error(WHERE, "The ceiling isn't valid", EXIT_FAILURE));
	tmp = safe_strdup(ZONE_1, texture->colors->color_floor);
	safe_free(ZONE_1, texture->colors->color_floor);
	if (update_color(&texture->colors->color_floor, tmp) == EXIT_FAILURE)
		nuclear_exit(ft_error(WHERE, "The floor isn't valid", EXIT_FAILURE));
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

int	check_format_fc(t_texture *texture)
{
	if (validate_color_format(texture->colors->color_ceiling) == EXIT_FAILURE)
		nuclear_exit(ft_error(WHERE, "The ceiling isn't valid", EXIT_FAILURE));
	if (validate_color_format(texture->colors->color_floor) == EXIT_FAILURE)
		nuclear_exit(ft_error(WHERE, "The floor isn't valid", EXIT_FAILURE));
	return (EXIT_SUCCESS);
}

int	validate_color_range(char *color)
{
	char	**splited;
	int		i;
	int		tmp;

	splited = safe_split(ZONE_1, color, ',');
	i = 0;
	while (splited[i])
	{
		tmp = ft_atoi(splited[i]);
		if (tmp < 0 || tmp > 255)
		{
			memory_manager(DEL_ELEM, ZONE_1, splited);
			return (EXIT_FAILURE);
		}
		i++;
	}
	memory_manager(DEL_ELEM, ZONE_1, splited);
	return (EXIT_SUCCESS);
}

int	verif_colors(t_texture *texture)
{
	if (validate_color_range(texture->colors->color_ceiling) == EXIT_FAILURE)
		nuclear_exit(ft_error(WHERE, "Format not valid", EXIT_FAILURE));
	if (validate_color_range(texture->colors->color_floor) == EXIT_FAILURE)
		nuclear_exit(ft_error(WHERE, "Format not valid", EXIT_FAILURE));
	return (EXIT_SUCCESS);
}
