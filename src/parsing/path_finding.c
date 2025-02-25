
#include "cub.h"
#include "parsing_interns.h"

static void	find_last_floor(t_parsing_map *p)
{
	int	i;
	int	j;

	i = 0;
	while (p->grid_copy[i])
	{
		j = 0;
		while (p->grid_copy[i][j])
		{
			if (p->grid_copy[i][j] == '0')
			{
				p->x_last_0 = i;
				p->y_last_0 = j;
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
	if (!cells[x][y])
		return (1);
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

int	check_wall(t_infos_p *infos_p)
{
	int	i;
	int	j;

	i = 0;
	while (infos_p->p->grid_copy[i])
	{
		j = 0;
		while (infos_p->p->grid_copy[i][j])
		{
			if (isset(infos_p->p->grid_copy[i][j], "NSEW0") == true)
			{
				find_last_floor(infos_p->p);
				if (path_finding(infos_p->p->x_last_0, \
				infos_p->p->y_last_0, infos_p->p->grid_copy) != 0)
					nuclear_exit(ft_error(WHERE, \
					"map not valid", EXIT_FAILURE));
			}
			j++;
		}
		i++;
	}
	return (EXIT_SUCCESS);
}

void	find_pos_player(t_game *game, char **grid)
{
	int	i;
	int	j;

	i = 0;
	while (grid[i])
	{
		j = 0;
		while (grid[i][j])
		{
			if (grid[i][j] == 'N' || grid[i][j] == 'S'
				|| grid[i][j] == 'E' || grid[i][j] == 'W')
			{
				game->player->facing = grid[i][j];
				game->player->position[X] = j;
				game->player->position[Y] = i;
				break ;
			}
			j++;
		}
		i++;
	}
}
