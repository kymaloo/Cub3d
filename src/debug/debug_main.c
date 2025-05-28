/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekrebs <ekrebs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 14:19:07 by ekrebs            #+#    #+#             */
/*   Updated: 2025/05/28 14:36:40 by ekrebs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	debug_main_post_parsing(t_game *game)
{
	print_debug_prefix(WHERE_FUNC, "");
	print_player_infos(game->player, "");
	printf(BWHITE"game hooks debug infos:"RESET"\n");
}

void	debug_main_prefix(char *name)
{
	int	tmp;

	tmp = 0;
	{
		while (tmp++ < 15)
			printf("\n\n\n");
		printf(BBLUE"\n%s:"BBLUE" executing program:" \
								BYELLOW" mode: Debug"RESET"\n\n\n", name);
		printf(BWHITE"parsing debug infos:"RESET"\n");
	}
}

void	debug_main_suffix(t_game *game, char *name)
{
	(void) game;
	printf(BBLUE"\n\n%s:"BBLUE" executing program:" \
											BGREEN" Done !\n"RESET, name);
}