/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekrebs <ekrebs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 20:32:01 by ekrebs            #+#    #+#             */
/*   Updated: 2025/05/28 20:41:34 by ekrebs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	ceilling(t_game *game, int x)
{
	int	y;

	y = 0;
	while (y < game->ray->draw_start)
	{
		mlx_put_pixel(game->texture->image->img_window, \
										x, y, game->colors->color_ceiling_uint);
		y++;
	}
}
