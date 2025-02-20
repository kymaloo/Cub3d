#include "cub.h"
#include "parsing_interns.h"

static void	find_last_floor(t_parsing_map *parse)
{
	int	i;
	int	j;

	i = 0;
	while (parse->grid_copy[i])
	{
		j = 0;
		while (parse->grid_copy[i][j])
		{
			if (parse->grid_copy[i][j] == '0')
			{
				parse->x_last_0 = i;
				parse->y_last_0 = j;
				return ;
			}
			j++;
		}
		i++;
	}
}

static bool	isset(char c, char *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (c == set[i])
			return (true);
		i++;
	}
	return (false);
}

static int	path_finding(int x, int y, char **cells)
{
	int	end;

	end = 0;
	if (isset(cells[x][y], "NSEW01D") == false)
		return (1);
	cells[x][y] = '1';
	if (isset(cells[x + 1][y], "1\n\0") == false)
		end += path_finding(x + 1, y, cells);
	if (isset(cells[x - 1][y], "1\n\0") == false)
		end += path_finding(x - 1, y, cells);
	if (isset(cells[x][y + 1], "1\n\0") == false)
		end += path_finding(x, y + 1, cells);
	if (isset(cells[x][y - 1], "1\n\0") == false)
		end += path_finding(x, y - 1, cells);
	return (end);
}

int	check_wall(t_mm *mm, t_parsing_map *parse)
{
	int	i;
	int	j;

	i = 0;
	while (parse->grid_copy[i])
	{
		j = 0;
		while (parse->grid_copy[i][j])
		{
			if (isset(parse->grid_copy[i][j], "NSEW0") == true)
			{
				find_last_floor(parse);
				if (path_finding(parse->x_last_0, \
				parse->y_last_0, parse->grid_copy) != 0)
					mm_nuclear_exit(mm, ft_error(WHERE, "map not valid", EXIT_FAILURE));
			}
			j++;
		}
		i++;
	}
	return (EXIT_SUCCESS);
}
