
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
	infos_p->g->map.map = extract_map(infos_p, infos_p->p->all_file);
	if (check_map(infos_p->g->map.map) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (check_doublon_map(infos_p->g->map.map, "NSEW") != 1)
		nuclear_exit(ft_error(WHERE, "ONE PLEYER PLSSSS 🤓", EXIT_FAILURE));
	find_pos_player(infos_p->g, infos_p->g->map.map);
	copy_map(infos_p);
	return (EXIT_SUCCESS);
}

static void	is_dir_and_filled(t_mlx_infos *mlx_infos)
{
	if (mlx_infos->paths.wall_east == NULL)
		nuclear_exit(ft_error(WHERE, "Path east is Null", EXIT_FAILURE));
	if (mlx_infos->paths.wall_west == NULL)
		nuclear_exit(ft_error(WHERE, "Path west is Null", EXIT_FAILURE));
	if (mlx_infos->paths.wall_north == NULL)
		nuclear_exit(ft_error(WHERE, "Path north is Null", EXIT_FAILURE));
	if (mlx_infos->paths.wall_south == NULL)
		nuclear_exit(ft_error(WHERE, "Path south is Null", EXIT_FAILURE));
	if (mlx_infos->colors.color_ceiling == NULL)
		nuclear_exit(ft_error(WHERE, "Path ceilling is Null", EXIT_FAILURE));
	if (mlx_infos->colors.color_floor == NULL)
		nuclear_exit(ft_error(WHERE, "Path floor is Null", EXIT_FAILURE));
}

void	init_infos_p(t_infos_p *infos_p, t_game *g, t_parsing_map *parsing_map)
{
	ft_memset(infos_p, 0, sizeof(t_infos_p));
	ft_memset(parsing_map, 0, sizeof(t_parsing_map));
	infos_p->g = g;
	infos_p->p = parsing_map;
}

int	parse_map_init_game_infos(t_game *game_infos, char *str)
{
	t_infos_p infos_p;
	t_parsing_map	p;

	init_infos_p(&infos_p, game_infos, &p);
	if (check_map_format_cub(str) == EXIT_FAILURE 
	|| check_map_reel(str) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	infos_p.p->all_file = stock_file(str);
	if (init_direction_and_fc(&infos_p, str) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	is_dir_and_filled(&game_infos->mlx_infos);
	if (all_line_is_valid(&infos_p.g->mlx_infos, infos_p.p->all_file) == 1)
		return (EXIT_FAILURE);
	if (check_fc(&game_infos->mlx_infos, infos_p.p) == EXIT_FAILURE
	|| check_format_fc(&game_infos->mlx_infos) == EXIT_FAILURE
	|| verif_colors(&game_infos->mlx_infos) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (init_map(&infos_p) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	memory_manager(DEL_ELEM, ZONE_1, infos_p.p->all_file);
	if (check_wall(&infos_p) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	char_to_rgb(game_infos->mlx_infos.colors, game_infos->mlx_infos.colors.color_ceiling, CEILING);
	char_to_rgb(game_infos->mlx_infos.colors, game_infos->mlx_infos.colors.color_floor, FLOOR);
	return (EXIT_SUCCESS);
}

int	all_line_is_valid(t_mlx_infos *mlx_infos, char **array)
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
		else if (ft_strncmp(array[i], mlx_infos->paths.wall_north, size) == 0
			|| ft_strncmp(array[i], mlx_infos->paths.wall_south, size) == 0)
			i++;
		else if (ft_strncmp(array[i], mlx_infos->paths.wall_east, size) == 0
			|| ft_strncmp(array[i], mlx_infos->paths.wall_west, size) == 0)
			i++;
		else if (ft_strncmp(array[i], \
			mlx_infos->colors.color_ceiling, size) == 0
			|| ft_strncmp(array[i], mlx_infos->colors.color_floor, size) == 0)
			i++;
		else
			nuclear_exit(ft_error(WHERE, "Line isn't valid", EXIT_FAILURE));
	}
	return (EXIT_SUCCESS);
}

void	char_to_rgb(t_colors colors, char *str, int id)
{
	char	**split;

	split = ft_split(&str[2], ',');
	if (split == NULL)
		return ;
	if (id == FLOOR)
		colors.color_floor_uint = get_rgba(ft_atoi(split[0]), ft_atoi(split[1]), ft_atoi(split[2]), 255);
	if (id == CEILING)
		colors.color_ceiling_uint = get_rgba(ft_atoi(split[0]), ft_atoi(split[1]), ft_atoi(split[2]), 255);
	ft_free_all(split, 0);
	return ;
}
