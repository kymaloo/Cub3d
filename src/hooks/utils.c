/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekrebs <ekrebs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 11:17:52 by ekrebs            #+#    #+#             */
/*   Updated: 2025/05/28 11:18:58 by ekrebs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

float	normalize_angle(float angle)
{
	while (angle < 0)
		angle += 2 * M_PI;
	while (angle >= 2 * M_PI)
		angle -= 2 * M_PI;
	return (angle);
}

void	update_player_direction(t_player *player)
{
	player->direction[0] = cos(player->radian);
	player->direction[1] = sin(player->radian);
}
