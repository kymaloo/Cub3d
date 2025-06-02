/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekrebs <ekrebs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 20:31:43 by ekrebs            #+#    #+#             */
/*   Updated: 2025/05/28 20:41:53 by ekrebs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

static void	onscreen_line(t_ray *ray, int line_height)
{
	if (line_height > HEIGHT * 10)
		line_height = HEIGHT * 10;
	ray->draw_start = -line_height / 2 + HEIGHT / 2;
	ray->draw_end = line_height / 2 + HEIGHT / 2;
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	if (ray->draw_end >= HEIGHT)
		ray->draw_end = HEIGHT - 1;
}

static void	init_ray_dir_x_y(t_ray *ray, t_player *player)
{
	if (ray->dir_x < 0)
	{
		ray->step_x = -1;
		ray->side_dist_x = (player->position[0] - ray->map_x) \
														* ray->delta_dist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist_x = (ray->map_x + 1.0 - player->position[0]) \
														* ray->delta_dist_x;
	}
	if (ray->dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = (player->position[1] - ray->map_y) \
														* ray->delta_dist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = (ray->map_y + 1.0 - player->position[1]) \
														* ray->delta_dist_y;
	}
}

static void	init_var_ray(t_ray *ray, t_player *player, float ray_angle)
{
	ray->dir_x = cos(ray_angle);
	ray->dir_y = sin(ray_angle);
	ray->map_x = (int)player->position[0];
	ray->map_y = (int)player->position[1];
	ray->delta_dist_x = fabs(1 / ray->dir_x);
	ray->delta_dist_y = fabs(1 / ray->dir_y);
	ray->hit = 0;
	init_ray_dir_x_y(ray, player);
}

static void	calculate_perp_wall_dist(t_game *game, float ray_angle)
{
	float	angle_diff;

	if (game->ray->side == 0)
		game->ray->perp_wall_dist = fabs((game->ray->map_x \
						- game->player->position[0] \
						+ (1 - game->ray->step_x) / 2) / game->ray->dir_x);
	else
		game->ray->perp_wall_dist = fabs((game->ray->map_y \
						- game->player->position[1] \
						+ (1 - game->ray->step_y) / 2) / game->ray->dir_y);
	angle_diff = game->player->radian - ray_angle;
	while (angle_diff > M_PI)
		angle_diff -= M_2_PI;
	while (angle_diff < -M_PI)
		angle_diff += M_2_PI;
	game->ray->realdist = game->ray->perp_wall_dist;
	game->ray->perp_wall_dist *= cos(angle_diff);
	if (game->ray->perp_wall_dist < 0.05)
		game->ray->perp_wall_dist = 0.05;
}

void	raycast(t_game *game)
{
	int		x;
	float	camera_x;
	float	ray_angle;

	x = 0;
	while (x < WIDTH)
	{
		camera_x = 2 * x / (float)WIDTH - 1;
		ray_angle = game->player->radian \
										+ atan(camera_x * tan(FOV_DEG));
		init_var_ray(game->ray, game->player, ray_angle);
		perform_dda(game->ray, game->map);
		calculate_perp_wall_dist(game, ray_angle);
		if (game->ray->perp_wall_dist < 0.1)
			game->ray->perp_wall_dist = 0.1;
		game->ray->line_height = (int)(HEIGHT / game->ray->perp_wall_dist);
		onscreen_line(game->ray, game->ray->line_height);
		setup_colors(game, x);
		x++;
	}
}
