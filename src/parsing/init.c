
#include "cub.h"
#include "parsing_interns.h"

static int	init_direction_and_fc(t_infos_p *infos_p, char *str)
{
	if (init_tab_direction(infos_p->p) == EXIT_FAILURE)
		nuclear_exit(ft_error(WHERE, "Init Tab Direction Failed", \
		EXIT_FAILURE));
	if (init_tab_fc(infos_p->p) == EXIT_FAILURE)
		nuclear_exit(ft_error(WHERE, "Init Tab Fc Failed", \
		EXIT_FAILURE));
	if (init_direction(infos_p, str, 0, 0) == EXIT_FAILURE)
		nuclear_exit(ft_error(WHERE, "Init Direction Failed", \
		EXIT_FAILURE));
	if (init_fc(infos_p, str) == EXIT_FAILURE)
		nuclear_exit(ft_error(WHERE, "Init Fc Failed", EXIT_FAILURE));
	return (EXIT_SUCCESS);
}

static int	init_map(t_infos_p *infos_p)
{
	infos_p->g->map = safe_calloc(ZONE_1, 1, sizeof(t_map));
	infos_p->g->map->map = extract_map(infos_p, infos_p->p->all_file);
	if (check_map(infos_p->g->map->map) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (check_doublon_map(infos_p->g->map->map, "NSEW") != 1)
		nuclear_exit(ft_error(WHERE, "ONE PLEYER PLSSSS 🤓", EXIT_FAILURE));
	find_pos_player(infos_p->g, infos_p->g->map->map);
	copy_map(infos_p);
	return (EXIT_SUCCESS);
}

static void	is_dir_and_filled(t_textures *textures)
{
	if (textures->path->path_east == NULL)
		nuclear_exit(ft_error(WHERE, "Path east is Null", EXIT_FAILURE));
	if (textures->path->path_west == NULL)
		nuclear_exit(ft_error(WHERE, "Path west is Null", EXIT_FAILURE));
	if (textures->path->path_north == NULL)
		nuclear_exit(ft_error(WHERE, "Path north is Null", EXIT_FAILURE));
	if (textures->path->path_south == NULL)
		nuclear_exit(ft_error(WHERE, "Path south is Null", EXIT_FAILURE));
	if (textures->colors->color_ceiling == NULL)
		nuclear_exit(ft_error(WHERE, "Path ceilling is Null", EXIT_FAILURE));
	if (textures->colors->color_floor == NULL)
		nuclear_exit(ft_error(WHERE, "Path floor is Null", EXIT_FAILURE));
}

int	init(t_infos_p *infos_p, char *str)
{
	if (check_map_format_cub(str) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (check_map_reel(str) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	infos_p->p->all_file = stock_file(str);
	if (init_direction_and_fc(infos_p, str) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	is_dir_and_filled(infos_p->g->textures);
	if (all_line_is_valid(infos_p->g->textures, infos_p->p->all_file) == 1)
		return (EXIT_FAILURE);
	if (check_fc(infos_p->g->textures, infos_p->p) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (check_format_fc(infos_p->g->textures) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (verif_colors(infos_p->g->textures) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (init_map(infos_p) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	memory_manager(DEL_ELEM, ZONE_1, infos_p->p->all_file);
	if (check_wall(infos_p) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	print_map(infos_p->g->map->map);
	return (EXIT_SUCCESS);
}

int	all_line_is_valid(t_textures *textures, char **array)
{
	int	i;
	int	size;

	i = 0;
	while (array[i])
	{
		size = ft_strlen_int(array[i]);
		if (check_white_space(array[i]) == 0 || \
		char_valid_for_map("01NSEWD\t ", array[i]) == 0)
			i++;
		else if (ft_strncmp(array[i], textures->path->path_north, size) == 0
			|| ft_strncmp(array[i], textures->path->path_south, size) == 0)
			i++;
		else if (ft_strncmp(array[i], textures->path->path_east, size) == 0
			|| ft_strncmp(array[i], textures->path->path_west, size) == 0)
			i++;
		else if (ft_strncmp(array[i], textures->colors->color_ceiling, size) == 0
			|| ft_strncmp(array[i], textures->colors->color_floor, size) == 0)
			i++;
		else
			nuclear_exit(ft_error(WHERE, "Line isn't valid", EXIT_FAILURE));
	}
	return (EXIT_SUCCESS);
}
