/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekrebs <ekrebs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 10:54:25 by ekrebs            #+#    #+#             */
/*   Updated: 2025/05/28 21:00:17 by ekrebs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	print_debug_prefix(char *file, int line, \
												const char *func, char *str_msg)
{
	printf(BLUE"%35s:"YELLOW"%-3d:"RESET"%-15s:    "BBLUE"\t%15s"RESET, \
													file, line, func, str_msg);
}

void	print_angle(float rad)
{
	printf(MAGENTA"%-5.2frad ", rad);
	if ((rad >= 15 * M_PI_BY_8 && rad < M_2_PI) \
											|| (rad >= 0 && rad < M_PI_BY_8))
		printf("(E)"RESET);
	else if (rad >= M_PI_BY_8 && rad < 3 * M_PI_BY_8)
		printf("(NE)"RESET);
	else if (rad >= 3 * M_PI_BY_8 && rad < 5 * M_PI_BY_8)
		printf("(N)"RESET);
	else if (rad >= 5 * M_PI_BY_8 && rad < 7 * M_PI_BY_8)
		printf("(NW)"RESET);
	else if (rad >= 7 * M_PI_BY_8 && rad < 9 * M_PI_BY_8)
		printf("(W)"RESET);
	else if (rad >= 9 * M_PI_BY_8 && rad < 11 * M_PI_BY_8)
		printf("(SW)"RESET);
	else if (rad >= 11 * M_PI_BY_8 && rad < 13 * M_PI_BY_8)
		printf("(S)"RESET);
	else if (rad >= 13 * M_PI_BY_8 && rad < 15 * M_PI_BY_8)
		printf("(SE)"RESET);
}

void	print_player_infos(t_player *player, char *str_prefix)
{
	printf("\n%s\n", str_prefix);
	printf("\tplayer position:\t("RED"%5.2f"RESET","GREEN" %5.2f"RESET")\n", \
									player->position[X], player->position[Y]);
	printf("\tplayer direction:\t("RED"%5.2f"RESET","GREEN" %5.2f"RESET") ", \
									player->direction[X], player->direction[Y]);
	printf("norm: %.2f ", sqrt(player->direction[X] * player->direction[X] \
								+ player->direction[Y] * player->direction[Y]));
	print_angle(player->radian);
	printf("\n");
}

void	print_map_infos(t_map *map, char *str_prefix)
{
	printf("\n%s\n", str_prefix);
	printf("\nmap max:\t("RED"%3d"RESET","GREEN" %3d"RESET")\n", \
												map->x_max -1, map->y_max - 1);
	printf("\n");
}

void	print_coord(char *str_prefix, char *str_suffix, float x, float y)
{
	printf("\t%15s  ("RED"%.2f"RESET", "GREEN"%.2f"RESET") %10s\n", \
												str_prefix, x, y, str_suffix);
}
