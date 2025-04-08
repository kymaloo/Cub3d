
#include "cub.h"
#include "parsing_interns.h"

int	count_line_in_file(char *str)
{
	int		fd;
	int		count;
	char	*line;

	fd = open_map(str);
	count = 0;
	line = safe_get_next_line(ZONE_1, fd);
	while (line != NULL)
	{
		safe_free(ZONE_1, line);
		count++;
		line = safe_get_next_line(ZONE_1, fd);
	}
	close_map(fd);
	return (count);
}

char	**stock_file(char *str)
{
	int		i;
	int		fd;
	int		count;
	char	**result;

	i = 0;
	fd = open_map(str);
	count = count_line_in_file(str);
	result = safe_malloc(ZONE_1, sizeof(char *) * (count + 1));
	if (!result)
		return (NULL);
	while (i < count)
	{
		result[i] = safe_get_next_line(ZONE_1, fd);
		i++;
	}
	result[i] = NULL;
	close_map(fd);
	return (result);
}

char	**extract_map(t_infos_p *infos_p, char **array)
{
	int		i;
	int		j;
	int		len;
	int		size;
	char	**result;

	i = 0;
	j = 0;
	size = get_size_of_array(&infos_p->g->mlx_infos, infos_p->p, array, 0);
	infos_p->g->map.y_max = size;
	get_line_size(infos_p, array);
	len = infos_p->g->map.x_max;
	result = safe_calloc(ZONE_1, 1, (sizeof(char *) * (size + 1)));
	if (!result)
		return (NULL);
	while (i != get_index_before_array(infos_p, array, 0))
		i++;
	while (array[i])
	{
		result[j] = safe_strdup_with_calloc(ZONE_1, array[i], len + 1);
		i++;
		j++;
	}
	result[j] = NULL;
	return (result);
}

void	copy_map(t_infos_p *infos_p)
{
	int		i;
	int		len;
	int		size;

	i = 0;
	size = infos_p->g->map.y_max;
	len = infos_p->g->map.x_max;
	infos_p->p->grid_copy = safe_calloc(ZONE_1, 1, sizeof(char *) * (size + 1));
	if (!infos_p->p->grid_copy)
		return ;
	while (infos_p->g->map.map[i])
	{
		infos_p->p->grid_copy[i] = safe_strdup_with_calloc(ZONE_1, \
		infos_p->g->map.map[i], len + 1);
		i++;
	}
	infos_p->p->grid_copy[i] = NULL;
}

int	char_valid_for_map(char *cmp, char *str)
{
	int	i;
	int	j;
	int	size;
	int	count;

	i = 0;
	count = 0;
	size = ft_strlen_int(str);
	while (str[i])
	{
		j = 0;
		while (cmp[j])
		{
			if (str[i] == cmp[j])
				count++;
			j++;
		}
		i++;
	}
	if (size != count)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
