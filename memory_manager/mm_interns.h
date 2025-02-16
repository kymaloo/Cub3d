/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mm_interns.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekrebs <ekrebs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 21:17:57 by ekrebs            #+#    #+#             */
/*   Updated: 2025/02/17 00:02:40 by ekrebs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MM_INTERNS_H
# define	MM_INTERNS_H
#include "memory_manager.h"

//utils


t_area_node		*create_area_node(t_mm *mm, char *new_area_name);
t_area_node		*go_to_area_name(t_mm *mm, char *area_name_to_find);
void			destroy_area_content(t_content_array *content_node);
t_content_array	*initialize_content_array(t_mm *mm, t_content_array *new);
void			upgrade_content_array_size(t_mm *mm, t_content_array *old);

size_t			findFirstZeroBit(const bool *bits, size_t length);


// destroy utils
void	destroy_content_array(t_content_array *content);
void	destroy_area_hahsmap(t_content_hashmap *hashmap);
void	destroy_area(t_area_node *area);
void	destroy_areas(t_area_node *areas);

#endif