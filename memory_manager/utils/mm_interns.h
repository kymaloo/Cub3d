/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mm_interns.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekrebs <ekrebs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 21:17:57 by ekrebs            #+#    #+#             */
/*   Updated: 2025/02/17 13:38:42 by ekrebs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MM_INTERNS_H
# define	MM_INTERNS_H
#include "memory_manager.h"

//utils

t_area_node		*create_area_node(t_mm *mm, char *new_area_name);
t_area_node		*go_to_area_name(t_mm *mm, char *area_name_to_find);
void			destroy_area_hahsmap_content(t_content_hashmap *hashmap);
t_content_array	*initialize_content_array(t_mm *mm, t_content_array *new);
void			upgrade_content_array_size(t_mm *mm, t_content_array *old);
size_t			findFirstZeroBit(const bool *bits, size_t length);

void			mm_hashmap_add(t_mm *mm, t_content_hashmap *hashmap, void *elem);
void			mm_hashmap_remove(t_mm *mm, t_content_hashmap *hashmap, void *elem);


// destroy utils

void	destroy_content_array(t_content_array *content);
void	destroy_area_hahsmap(t_content_hashmap *hashmap);
void	destroy_area(t_area_node *area);
void	destroy_areas(t_area_node *areas);

#endif