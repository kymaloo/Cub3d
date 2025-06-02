/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekrebs <ekrebs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 09:24:37 by ekrebs            #+#    #+#             */
/*   Updated: 2025/05/28 20:37:42 by ekrebs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DDA_H
# define DDA_H

bool	is_within_map_boundaries(t_map *map, int x, int y);
void	update_player_direction(t_player *player);
float	normalize_angle(float angle);

void	setup_colors(t_game *game, int x);
void	ceilling(t_game *game, int x);

#endif