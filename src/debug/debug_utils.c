#include "cub.h"


void	print_debug_prefix(char *file, int line, const char *func, char *str_msg)
{
	printf(BLUE"%35s:"YELLOW"%-3d:"RESET"%-15s:    "BBLUE"\t%15s\t"RESET, file, line, func, str_msg);
}

void	print_angle(float rad)
{
	printf(MAGENTA"%-5.2frad ", rad);
	if ((rad >= 15*M_PI/8 && rad < 2*M_PI) || (rad >= 0 && rad < M_PI/8))
		printf("(E)"RESET);
	else if (rad >= M_PI/8 && rad < 3*M_PI/8)
		printf("(NE)"RESET);
	else if (rad >= 3*M_PI/8 && rad < 5*M_PI/8)
		printf("(N)"RESET);
	else if (rad >= 5*M_PI/8 && rad < 7*M_PI/8)
		printf("(NW)"RESET);
	else if (rad >= 7*M_PI/8 && rad < 9*M_PI/8)
		printf("(W)"RESET);
	else if (rad >= 9*M_PI/8 && rad < 11*M_PI/8)
		printf("(SW)"RESET);
	else if (rad >= 11*M_PI/8 && rad < 13*M_PI/8)
		printf("(S)"RESET);
	else if (rad >= 13*M_PI/8 && rad < 15*M_PI/8)
		printf("(SE)"RESET);
}

void	print_player_infos(t_player* player, char *str_prefix)
{
	printf("\n%s\n", str_prefix);
	printf("\tplayer position:\t("RED"%5.2f"RESET","GREEN" %5.2f"RESET")\n", player->position[X], player->position[Y]);
	printf("\tplayer direction:\t("RED"%5.2f"RESET","GREEN" %5.2f"RESET") ", player->direction[X], player->direction[Y]);
	printf("norm: %.2f ", sqrt(player->direction[X] * player->direction[X] + player->direction[Y] * player->direction[Y]));
	print_angle(player->radian);
	printf("\n");
}

void	print_map_infos(t_map* map, char *str_prefix)
{
	printf("\n%s\n", str_prefix);
	printf("\nmap max:\t("RED"%3d"RESET","GREEN" %3d"RESET")\n", map->x_max -1, map->y_max - 1);
	printf("\n");
}


void	print_coord(char *str_prefix, char *str_suffix, float x, float y)
{
	printf("\t%15s  ("RED"%.2f"RESET", "GREEN"%.2f"RESET") %10s\n", str_prefix, x, y, str_suffix);
}

#define OFFSET 1
void	print_map_tile(char map_char)
{
	if (map_char == '1')
		printf(BWHITE"[]"RESET);
	else if (map_char == '0') 
		printf(" ."RESET);
	else if (map_char == 'D')
		printf("{}"RESET);
	else if (map_char == 'P')
		printf(BBLUE"()"RESET);
	else
		printf(MAGENTA"ER"RESET);
}

void	print_map_around(t_game *g, int x, int y, int offset)
{
	int xmin, xmax, ymin, ymax, i, j;

	xmin = x - offset;
	xmax = x + offset;
	ymin = y - offset;
	ymax = y + offset;

	if (xmin < 0)
		xmin = 0;
	if (xmax >= g->map->x_max)
		xmax = g->map->x_max -1;
	if (ymin < 0)
		ymin = 0;
	if (ymax >= g->map->y_max)
		ymax = g->map->y_max -1;

	
	printf("\ncurrent grid situation: \n");
	j = ymin;
	while(j <= ymax)
	{
		i = xmin;
		while(i <= xmax)
		{
			print_map_tile(g->map->grid[j][i]);
			i++;
		}
		printf("\n");
		j++;
	}
}

void	print_map_around_a_highlight_b(t_game *g, int xa, int ya, int xb, int yb, int offset)
{
	int xmin, xmax, ymin, ymax, i, j;

	xmin = xa - offset;
	xmax = xa + offset;
	ymin = ya - offset;
	ymax = ya + offset;

	if (xmin < 0)
		xmin = 0;
	if (xmax > g->map->x_max -1)
		xmax = g->map->x_max -1;
	if (ymin < 0)
		ymin = 0;
	if (ymax > g->map->y_max -1)
		ymax = g->map->y_max -1;

	print_coord("player is:", "", xa, ya);
	print_coord("trying move:", "", xb, yb);
	printf("\ncurrent grid situation: \n");
	j = ymin;
	while(j <= ymax)
	{
		i = xmin;
		while(i <= xmax)
		{
			if (i == xb && j == yb)
				printf(BGBLUE"");
			if (i == xa && j == ya)
				printf(BBLUE"xx"RESET);
			else
				print_map_tile(g->map->grid[j][i]);
			i++;
		}
		printf("\n");
		j++;
	}
}

void	print_map_player(t_game *g, int offset)
{
	int xmin, xmax, ymin, ymax, i, j;
	int	xa, ya, xt, yt;
	float xb, yb;

	t_player *p = g->player;
	
	xa = p->position[X]; 
	ya = p->position[Y]; 
	xb = p->position[X] + p->direction[X] * 0.3; 
	yb = p->position[Y] + p->direction[Y] * 0.3;


	xmin = xa - offset;
	xmax = xa + offset;
	ymin = ya - offset;
	ymax = ya + offset;

	if (xmin < 0)
		xmin = 0;
	if (xmax > g->map->x_max -1)
		xmax = g->map->x_max -1;
	if (ymin < 0)
		ymin = 0;
	if (ymax > g->map->y_max -1)
		ymax = g->map->y_max -1;





	print_coord("player is:", "", xa, ya);
	print_coord("targeting move:", "", xb, yb);
	xt = xb;
	yt = yb;
	print_coord("targeting grid:", "", xt, yt);
	printf("\ncurrent grid situation: \n");
	j = ymin;
	while(j <= ymax)
	{
		i = xmin;
		while(i <= xmax)
		{
			if (i == xt && j == yt)
				printf(BGBLUE""); //highlight target background in BBLUE
			if (i == xa && j == ya)
				printf(BBLUE"xx"RESET);
			else
				print_map_tile(g->map->grid[j][i]);
			i++;
		}
		printf("\n");
		j++;
	}
}