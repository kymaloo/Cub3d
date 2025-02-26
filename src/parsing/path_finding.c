
#include "cub.h"
#include "parsing_interns.h"

static void	find_last_floor(t_parsing_map *p)
{
	int y;
	int	x;

	y = 0;
	while (p->grid_copy[y])
	{
		x = 0;
		while (p->grid_copy[y][x])
		{
			if (p->grid_copy[y][x] == '0')
			{
				p->x_last_0 = x;
				p->y_last_0 = y;
				return ;
			}
			x++;
		}
		y++;
	}
}

bool	isset(char c, char *set)
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


static void flood_fill_rec(int x, int y, t_infos_p *ip, int i)
{
	char	**cells;
	char	*legal_grid_chars;
	
	legal_grid_chars = "NSEW01D";
	cells = ip->p->grid_copy;

	if (x < 0 || x > ip->g->map->x_max || y < 0 || y > ip->g->map->y_max)
		nuclear_exit(ft_error(WHERE, "map walling not valid: entering illegal coords territory (very scary stuff)", EXIT_FAILURE));
	if (isset(cells[y][x], legal_grid_chars) == false)
		nuclear_exit(ft_error(WHERE, "map walling not valid: illegal char used", EXIT_FAILURE));

	if (cells[y][x] == '1')
		return ;
	printf(BLUE"\n\ni: %d: [Y][X] = [%d][%d]\n"RESET, i, y, x);
	print_map_highlight(cells, x, y);
	
	cells[y][x] = '1';
	i = i + 1;
	flood_fill_rec(x, y + 1, ip, i);
	flood_fill_rec(x, y - 1, ip, i);
	flood_fill_rec(x + 1, y, ip, i);
	flood_fill_rec(x - 1, y, ip, i);
	return ;
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
				//printf("pathfinding n*%d starts in [Y][X] = [%d][%d]\n", id++, infos_p->p->y_last_0, infos_p->p->x_last_0);
				flood_fill_rec(infos_p->p->x_last_0, infos_p->p->y_last_0, infos_p, 1);
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
