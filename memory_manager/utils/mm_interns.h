/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mm_interns.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekrebs <ekrebs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 21:17:57 by ekrebs            #+#    #+#             */
/*   Updated: 2025/02/21 11:10:39 by ekrebs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MM_INTERNS_H
# define	MM_INTERNS_H
#include "memory_manager.h"

//utils

t_area_node		*create_area_node(t_mm *mm, char *new_area_name, t_deletion_func deletion_func, size_t nb_hahsmap_buckets);
t_area_node		*go_to_area_name(t_mm *mm, char *area_name_to_find);
void			destroy_area_hahsmap_content(t_content_hashmap *hashmap);
t_content_array	*initialize_content_array(t_mm *mm, t_content_array *new);
void			upgrade_content_array_size(t_mm *mm, t_content_array *old);
size_t			findFirstZeroBit(const bool *bits, size_t length);

void			mm_hashmap_init(t_mm *mm, t_content_hashmap *h, size_t nb_buckets);

void			mm_hashmap_add(t_mm *mm, t_content_hashmap *hashmap, void *elem);
void			mm_hashmap_remove(t_mm *mm, t_content_hashmap *hashmap, void *elem);

t_status		ft_strcmp(char *s1, char *s2);

// destroy utils

void	destroy_content_array(t_content_array *content, t_deletion_func deletion_func);
void	destroy_area_hahsmap(t_content_hashmap *hashmap);
void	destroy_area(t_area_node *area);
void	destroy_areas(t_area_node *areas);


//memory_manager

void	mm_create(t_mm **mm);
void	mm_destroy(t_mm *mm);

void	mm_area_create(t_mm *mm, char *area_name, t_area_create_data *a);
void	mm_area_delete(t_mm *mm, char *area_name);

void	mm_area_add_elem(t_mm *mm, char *area, void *elem);
void	mm_area_free_elem(t_mm *mm, char *area, void *elem);

void	mm_nuclear_exit(t_mm *mm, t_status status);

#endif