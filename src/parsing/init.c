#include "cub.h"
#include "parsing_interns.h"

static int	init_direction_and_fc(t_mm *mm, t_parsing_map *parse, char *str)
{
	if (init_tab_direction(mm, parse) == EXIT_FAILURE)
		mm_nuclear_exit(mm, ft_error(WHERE, "Init Tab Direction Failed", EXIT_FAILURE));
	if (init_tab_fc(mm, parse) == EXIT_FAILURE)
		mm_nuclear_exit(mm, ft_error(WHERE, "Init Tab Fc Failed", EXIT_FAILURE));
	if (init_direction(mm, parse, str, 0, 0) == EXIT_FAILURE)
		mm_nuclear_exit(mm, ft_error(WHERE, "Init Direction Failed", EXIT_FAILURE));
	if (init_fc(mm, parse, str) == EXIT_FAILURE)
		mm_nuclear_exit(mm, ft_error(WHERE, "Init Fc Failed", EXIT_FAILURE));
	return (EXIT_SUCCESS);
}

static int	init_map(t_mm *mm, t_parsing_map *parse, char *str)
{
	parse->grid_and_dir = stock_file(mm, str);
	parse->grid = extract_map(mm, parse, parse->grid_and_dir, str);
	if (check_map(parse->grid) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (check_doublon_map(parse->grid, "NSEW") != 1)
		mm_nuclear_exit(mm, ft_error(WHERE, "ONE PLEYER PLSSSS 🤓", EXIT_FAILURE));
	copy_map(mm, parse);
	return (EXIT_SUCCESS);
}

int	init(t_mm *mm, t_parsing_map *parse, char *str)
{
	if (check_map_format_cub(mm, str) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (check_map_reel(mm, str) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (init_direction_and_fc(mm, parse, str) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (check_fc(mm, parse) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (check_format_fc(mm, parse) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (verif_colors(mm, parse) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	count_line(mm, parse, str, 0);
	line_size(mm, parse, str, 0);
	if (init_map(mm, parse, str) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (check_wall(mm, parse) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
