/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekrebs <ekrebs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 09:24:15 by ekrebs            #+#    #+#             */
/*   Updated: 2025/06/18 02:13:13 by ekrebs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_H
# define CUB_H

# include <stdio.h>
# include <fcntl.h>
# include <stdbool.h>
# include <math.h>
# include "define.h"
# include "struct.h"
# include "../libft/libft.h"
# include "memory_manager.h"
# include "ft_error.h"
# include "MLX42/MLX42.h"
# include "MLX42/MLX42_Int.h"
# include "dda.h"
# include "debug.h"
# include "game_hooks.h"

int		init(t_data *data, char *str);
void	draw_map(t_game *g);
void	ft_hook(void *gamed);
void	print_minimap(t_game *g);
void	ft_move_perso(t_game *g);
void	create_memory_manager(t_data **data);
void	stock_radian(t_player *player);
bool	isset(char c, char *set);
void	print_map(char **map);
int		is_wall(t_map *map, int x, int y);
void	ft_move_perso(t_game *g);

void	raycast(t_game *game);
void	perform_dda(t_ray *ray, t_map *map);
void	init_textures(t_game *game);

void	init_mlx(t_game *game);
void	init_spawn_player(t_player *player);
void	mirror_mlx_texture_t(mlx_texture_t *texture);

#endif