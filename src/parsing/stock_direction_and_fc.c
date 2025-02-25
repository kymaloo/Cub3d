
#include "cub.h"
#include "parsing_interns.h"

static void	save_path(t_texture *texture, char *line, int dir_index)
{
	if (dir_index == 0)
		texture->path->north = safe_strdup(ZONE_1, line);
	else if (dir_index == 1)
		texture->path->south = safe_strdup(ZONE_1, line);
	else if (dir_index == 2)
		texture->path->west = safe_strdup(ZONE_1, line);
	else if (dir_index == 3)
		texture->path->east = safe_strdup(ZONE_1, line);
	else if (dir_index == 4)
		texture->colors->color_floor = safe_strdup(ZONE_1, line);
	else if (dir_index == 5)
		texture->colors->color_ceiling = safe_strdup(ZONE_1, line);
}

static	int	check_doublon(char *direction, char *line, int fd)
{
	printf("Error: Find duplicate for %s\n", direction);
	safe_free(ZONE_1, line);
	close_map(fd);
	return (EXIT_FAILURE);
}

int	process_direction(t_infos_p *infos_p, char *line, int dir_i, int fd)
{
	if (dir_i == 0 && infos_p->g->texture->path->north != NULL)
		return (check_doublon("north", line, fd));
	if (dir_i == 1 && infos_p->g->texture->path->south != NULL)
		return (check_doublon("south", line, fd));
	if (dir_i == 2 && infos_p->g->texture->path->west != NULL)
		return (check_doublon("west", line, fd));
	if (dir_i == 3 && infos_p->g->texture->path->east != NULL)
		return (check_doublon("east", line, fd));
	if (dir_i == 4 && infos_p->g->texture->colors->color_floor != NULL)
		return (check_doublon("floor", line, fd));
	if (dir_i == 5 && infos_p->g->texture->colors->color_ceiling != NULL)
		return (check_doublon("ceiling", line, fd));
	save_path(infos_p->g->texture, line, dir_i);
	return (EXIT_SUCCESS);
}

int	count_dir_in_file(t_parsing_map *p, char **dir)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (p->all_file[i])
	{
		if (strncmp_with_array(p->all_file[i], dir, 5) != -1)
		{
			count++;
			i++;
		}
		else
			i++;
	}
	return (count);
}

int	count_fc_in_file(t_parsing_map *p, char **dir)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (p->all_file[i])
	{
		if (strncmp_with_array(p->all_file[i], dir, 2) != -1)
		{
			count++;
			i++;
		}
		else
			i++;
	}
	return (count);
}
