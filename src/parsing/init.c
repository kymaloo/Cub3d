
#include "cub.h"
#include "parsing_interns.h"

static int	init_direction_and_fc(t_data *data, char *str)
{
	if (init_tab_direction(data->parse) == EXIT_FAILURE)
		nuclear_exit(ft_error(WHERE, "Init Tab Direction Failed",
		EXIT_FAILURE));
	if (init_tab_fc(data->parse) == EXIT_FAILURE)
		nuclear_exit(ft_error(WHERE, "Init Tab Fc Failed",
		EXIT_FAILURE));
	if (init_direction(data, str, 0, 0) == EXIT_FAILURE)
		nuclear_exit(ft_error(WHERE, "Init Direction Failed",
		EXIT_FAILURE));
	if (init_fc(data, str) == EXIT_FAILURE)
		nuclear_exit(ft_error(WHERE, "Init Fc Failed", EXIT_FAILURE));
	return (EXIT_SUCCESS);
}

static int	init_map(t_data *data)
{
	data->game->map = safe_calloc(ZONE_PARSE, 1, sizeof(t_map));
	data->game->map->grid = extract_map(data, data->parse->all_file);
	if (check_map(data->game->map->grid) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (check_doublon_map(data->game->map->grid, "NSEW") != 1)
		nuclear_exit(ft_error(WHERE, "ONE PLEYER PLSSSS 🤓", EXIT_FAILURE));
	find_pos_player(data->game, data->game->map->grid);
	copy_map(data);
	return (EXIT_SUCCESS);
}

static void	is_dir_and_filled(t_data *data)
{
	if (data->game->path->east == NULL)
		nuclear_exit(ft_error(WHERE, "Path east is Null", EXIT_FAILURE));
	if (data->game->path->west == NULL)
		nuclear_exit(ft_error(WHERE, "Path west is Null", EXIT_FAILURE));
	if (data->game->path->north == NULL)
		nuclear_exit(ft_error(WHERE, "Path north is Null", EXIT_FAILURE));
	if (data->game->path->south == NULL)
		nuclear_exit(ft_error(WHERE, "Path south is Null", EXIT_FAILURE));
	if (data->colors->color_ceiling == NULL)
		nuclear_exit(ft_error(WHERE, "Path ceilling is Null", EXIT_FAILURE));
	if (data->colors->color_floor == NULL)
		nuclear_exit(ft_error(WHERE, "Path floor is Null", EXIT_FAILURE));
}

int	init(t_data *data, char *str)
{
	if (check_map_format_cub(str) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (check_map_reel(str) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	data->parse->all_file = stock_file(str);
	if (init_direction_and_fc(data, str) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	is_dir_and_filled(data);
	if (all_line_is_valid(data, data->parse->all_file) == 1)
		return (EXIT_FAILURE);
	if (check_fc(data) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (check_format_fc(data->colors) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (verif_colors(data->colors) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (init_map(data) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	// printf("%d\n", data->game->map->x_max);
	// printf("%d\n", data->game->map->y_max);
	//print_map(data->parse->grid_copy);
	memory_manager(DEL_ELEM, ZONE_PARSE, data->parse->all_file);
	if (check_wall(data) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	
	return (EXIT_SUCCESS);
}

int	all_line_is_valid(t_data *data, char **array)
{
	int	i;
	int	size;

	i = 0;
	while (array[i])
	{
		size = ft_strlen_int(array[i]);
		if (check_white_space(array[i]) == 0 || 
		char_valid_for_map("01NSEWD\t ", array[i]) == 0)
			i++;
		else if (ft_strncmp(array[i], data->game->path->north, size) == 0
			|| ft_strncmp(array[i], data->game->path->south, size) == 0)
			i++;
		else if (ft_strncmp(array[i], data->game->path->east, size) == 0
			|| ft_strncmp(array[i], data->game->path->west, size) == 0)
			i++;
		else if (ft_strncmp(array[i], 
			data->colors->color_ceiling, size) == 0
			|| ft_strncmp(array[i], data->colors->color_floor, size) == 0)
			i++;
		else
			nuclear_exit(ft_error(WHERE, "Line isn't valid", EXIT_FAILURE));
	}
	return (EXIT_SUCCESS);
}
