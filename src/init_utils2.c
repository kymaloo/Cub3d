/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekrebs <ekrebs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 02:08:28 by ekrebs            #+#    #+#             */
/*   Updated: 2025/06/18 02:15:25 by ekrebs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

// <4 for R, G, B + transparency values of the pixels.
static void	swap_texture_pixels(uint8_t *pixels, int left, int right)
{
	uint8_t	ith_pixel;
	uint8_t	tmp;

	ith_pixel = 0;
	while (ith_pixel < 4)
	{
		tmp = pixels[left + ith_pixel];
		pixels[left + ith_pixel] = pixels[right + ith_pixel];
		pixels[right + ith_pixel] = tmp;
		ith_pixel++;
	}
}

void	mirror_mlx_texture_t(mlx_texture_t *texture)
{
	uint32_t	x;
	uint32_t	y;
	uint32_t	left;
	uint32_t	right;

	if (!texture)
		nuclear_exit(ft_error(__FILE__":", __LINE__, \
									"Texture mirror failed", EXIT_FAILURE));
	y = 0;
	while (y < texture->height)
	{
		x = 0;
		while (x < texture->width / 2)
		{
			left = (y * texture->width + x) * 4;
			right = (y * texture->width + (texture->width - x - 1)) * 4;
			swap_texture_pixels(texture->pixels, left, right);
			x++;
		}
		y++;
	}
}
