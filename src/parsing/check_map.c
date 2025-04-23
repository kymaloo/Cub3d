
#include "cub.h"
#include "parsing_interns.h"

int	check_map_format_cub(char *str)
{
	int	len_str;

	len_str = ft_strlen(str);
	if (len_str > 4)
	{
		if (ft_strncmp(&str[len_str - 4], ".cub", 4) == 0)
			return (EXIT_SUCCESS);
		else
			nuclear_exit(ft_error(WHERE, \
			"check_map_format_cub() failure", EXIT_FAILURE));
	}
	else
	{
		nuclear_exit(ft_error(WHERE, \
		"check_map_format_cub() failure", EXIT_FAILURE));
	}
	return (EXIT_FAILURE);
}

int	check_white_space(char *str)
{
	int	i;

	i = 0;
	if (str == NULL)
		return (1);
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '\0')
		return (0);
	return (1);
}

int	check_map(char **map)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] != '1' && map[i][j] != '0' &&
			map[i][j] != 'N' && map[i][j] != 'S' &&
			map[i][j] != 'E' && map[i][j] != 'W' &&
			is_white_space(map[i][j]) != 0 &&
			map[i][j] != 'D')
				return (printf("Error: The map is not ready!\n"), 1);
			j++;
		}
		i++;
	}
	return (0);
}

int	check_doublon_map(char **map, char *str)
{
	int	i;
	int	j;
	int	k;
	int	count;

	i = 0;
	count = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			k = 0;
			while (str[k])
			{
				if (map[i][j] == str[k])
					count++;
				k++;
			}
			j++;
		}
		i++;
	}
	return (count);
}

int	update_color(char **color, char *tmp)
{
	int	i;
	int	j;

	i = 2;
	j = 0;
	*color = safe_malloc(ZONE_1, sizeof(char) * (ft_strlen_int(tmp) - 1));
	if (!*color)
	{
		safe_free(ZONE_1, tmp);
		return (EXIT_FAILURE);
	}
	while (tmp[i])
	{
		(*color)[j] = tmp[i];
		j++;
		i++;
	}
	(*color)[j] = '\0';
	safe_free(ZONE_1, tmp);
	return (EXIT_SUCCESS);
}
