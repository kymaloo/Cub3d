#include "cub.h"
#include "parsing_interns.h"

int	check_fc(t_game *game)
{
	char	*tmp;

	game->parse->color_ceiling_cp = safe_strdup(game->mm, ZONE_1, game->parse->color_ceiling);
	game->parse->color_floor_cp = safe_strdup(game->mm, ZONE_1, game->parse->color_floor);
	if (ft_isdigit(game->parse->color_ceiling[2]) || ft_isdigit(game->parse->color_floor[2]))
		mm_nuclear_exit(game->mm, ft_error(WHERE, "The ceiling or floor isn't valid", EXIT_FAILURE));
	tmp = safe_strdup(game->mm, ZONE_1, game->parse->color_ceiling);
	safe_free(game->mm, ZONE_1, game->parse->color_ceiling);
	if (update_color(game, &game->parse->color_ceiling, tmp) == EXIT_FAILURE)
		mm_nuclear_exit(game->mm, ft_error(WHERE, "The ceiling isn't valid", EXIT_FAILURE));
	tmp = safe_strdup(game->mm, ZONE_1,game->parse->color_floor);
	safe_free(game->mm, ZONE_1, game->parse->color_floor);
	if (update_color(game, &game->parse->color_floor, tmp) == EXIT_FAILURE)
		mm_nuclear_exit(game->mm, ft_error(WHERE, "The floor isn't valid", EXIT_FAILURE));
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

int	check_format_fc(t_mm *mm,t_parsing_map *parse)
{
	if (validate_color_format(parse->color_ceiling) == EXIT_FAILURE)
		mm_nuclear_exit(mm, ft_error(WHERE, "The ceiling isn't valid", EXIT_FAILURE));
	if (validate_color_format(parse->color_floor) == EXIT_FAILURE)
		mm_nuclear_exit(mm, ft_error(WHERE, "The floor isn't valid", EXIT_FAILURE));
	return (EXIT_SUCCESS);
}

int	validate_color_range(t_mm *mm, char *color)
{
	char	**splited;
	int		i;
	int		tmp;

	splited = safe_split(mm, ZONE_PARSING_TMP, color, ',');
	i = 0;
	while (splited[i])
	{
		tmp = ft_atoi(splited[i]);
		if (tmp < 0 || tmp > 255)
		{
			mm_area_free_elem(mm, ZONE_PARSING_TMP, splited);
			return (EXIT_FAILURE);
		}
		i++;
	}
	mm_area_free_elem(mm, ZONE_PARSING_TMP, splited);
	return (EXIT_SUCCESS);
}

int	verif_colors(t_game *game)
{
	if (validate_color_range(game->mm, game->parse->color_ceiling) == EXIT_FAILURE)
		mm_nuclear_exit(game->mm, ft_error(WHERE, "Format not valid", EXIT_FAILURE));
	if (validate_color_range(game->mm, game->parse->color_floor) == EXIT_FAILURE)
		mm_nuclear_exit(game->mm, ft_error(WHERE, "Format not valid", EXIT_FAILURE));
	return (EXIT_SUCCESS);
}
