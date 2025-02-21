/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_direction_and_fc.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekrebs <ekrebs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 15:08:41 by trgaspar          #+#    #+#             */
/*   Updated: 2025/02/21 16:58:40 by ekrebs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"
#include "parsing_interns.h"

int	init_tab_direction(t_parsing_map *p)
{
	int	i;

	i = 0;
	p->direction = safe_malloc(ZONE_1, sizeof(char *) * 6);
	if (!p->direction)
		nuclear_exit(ft_error(WHERE, "malloc failure", MALLOC_ERROR));
	p->direction[i] = safe_strdup(ZONE_1, "NO ./");
	i++;
	p->direction[i] = safe_strdup(ZONE_1, "SO ./");
	i++;
	p->direction[i] = safe_strdup(ZONE_1, "WE ./");
	i++;
	p->direction[i] = safe_strdup(ZONE_1, "EA ./");
	i++;
	p->direction[i] = NULL;
	return (EXIT_SUCCESS);
}

int	init_tab_fc(t_parsing_map *p)
{
	int	i;

	i = 0;
	p->fc = safe_malloc(ZONE_1, sizeof(char *) * 3);
	if (!p->fc)
		nuclear_exit(ft_error(WHERE, "malloc failure", MALLOC_ERROR));
	p->fc[i] = safe_strdup(ZONE_1, "F ");
	i++;
	p->fc[i] = safe_strdup(ZONE_1, "C ");
	i++;
	p->fc[i] = NULL;
	return (EXIT_SUCCESS);
}

int	init_fc(t_infos_p *infos, char *str)
{
	int		i;
	int		fd;
	int		fc;

	i = 0;
	fc = count_fc_in_file(infos, infos->p->fc);
	if (fc != 2)
		return (EXIT_FAILURE);
	fd = open_map(str);
	while (infos->p->all_file[i])
	{
		if (ft_strncmp(infos->p->all_file[i], infos->p->fc[0], 2) == 0)
			process_direction(infos, infos->p->all_file[i], 4, fd);
		else if (ft_strncmp(infos->p->all_file[i], \
		infos->p->fc[1], 2) == 0)
			process_direction(infos, infos->p->all_file[i], 5, fd);
		i++;
	}
	return (close_map(fd));
}

int	init_direction(t_parsing_map *p, char *str, int dir, int fd)
{
	int		i;

	i = 0;
	dir = count_dir_in_file(infos, infos->p->direction);
	if (dir != 4)
		return (EXIT_FAILURE);
	fd = open_map(str);
	while (infos->p->all_file[i])
	{
		if (ft_strncmp(infos->p->all_file[i], \
		infos->p->direction[0], 5) == 0)
			process_direction(infos, infos->p->all_file[i], 0, fd);
		else if (ft_strncmp(infos->p->all_file[i], \
		infos->p->direction[1], 5) == 0)
			process_direction(infos, infos->p->all_file[i], 1, fd);
		else if (ft_strncmp(infos->p->all_file[i], \
		infos->p->direction[2], 5) == 0)
			process_direction(infos, infos->p->all_file[i], 2, fd);
		else if (ft_strncmp(infos->p->all_file[i], \
		infos->p->direction[3], 5) == 0)
			process_direction(infos, infos->p->all_file[i], 3, fd);
		i++;
	}
	return (close_map(fd));
}

int	check_map_reel(char *str)
{
	int	fd;

	fd = open_map(str);
	if (fd == -1)
		nuclear_exit(ft_error(WHERE, \
		"check_map_reel() failure", EXIT_FAILURE));
	return (EXIT_SUCCESS);
}
