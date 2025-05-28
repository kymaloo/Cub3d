/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_wall.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekrebs <ekrebs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 20:27:37 by ekrebs            #+#    #+#             */
/*   Updated: 2025/05/28 20:41:46 by ekrebs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

static void	setup_texture(t_game *game)
{
	if (game->ray->side == 0)
	{
		if (game->ray->dir_x < 0)
			game->ray->current_texture = game->texture->west;
		else
			game->ray->current_texture = game->texture->east;
	}
	else
	{
		if (game->ray->dir_y < 0)
			game->ray->current_texture = game->texture->south;
		else
			game->ray->current_texture = game->texture->north;
	}
}

static void	draw_column(t_game *game, t_ray *ray, float wall_x, int x)
{
	int		tex_x;
	int		tex_y;
	int		y;
	float	step;
	float	tex_pos;

	tex_x = (int)(wall_x * ray->current_texture->width);
	if (ray->side == 0 && ray->dir_x < 0)
		tex_x = ray->current_texture->width - tex_x - 1;
	if (ray->side == 1 && ray->dir_y < 0)
		tex_x = ray->current_texture->width - tex_x - 1;
	step = 1.0 * ray->current_texture->height / ray->line_height;
	tex_pos = (ray->draw_start - HEIGHT / 2 + ray->line_height / 2) * step;
	y = ray->draw_start;
	while (y <= ray->draw_end)
	{
		tex_y = (int)tex_pos & (int)(ray->current_texture->height - 1);
		tex_pos += step;
		ray->pixel = &ray->current_texture->pixels[(tex_x + tex_y \
										* ray->current_texture->width) * 4];
		ray->color = (ray->pixel[0] << 24) | (ray->pixel[1] << 16) \
										| (ray->pixel[2] << 8) | ray->pixel[3];
		mlx_put_pixel(game->texture->image->img_window, x, y, ray->color);
		y++;
	}
}

static void	wall(t_game *game, int x)
{
	float	wall_x;

	if (game->ray->side == 0)
		wall_x = game->player->position[1] \
									+ game->ray->realdist * game->ray->dir_y;
	else
		wall_x = game->player->position[0] \
									+ game->ray->realdist * game->ray->dir_x;
	wall_x -= floor(wall_x);
	setup_texture(game);
	draw_column(game, game->ray, wall_x, x);
}

static void	floors(t_game *game, int x)
{
	int	y;

	y = game->ray->draw_end + 1;
	while (y < HEIGHT)
	{
		mlx_put_pixel(game->texture->image->img_window, \
										x, y, game->colors->color_floor_uint);
		y++;
	}
}

void	setup_colors(t_game *game, int x)
{
	ceilling(game, x);
	wall(game, x);
	floors(game, x);
}
