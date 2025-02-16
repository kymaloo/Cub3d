/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mm_elem.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekrebs <ekrebs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 19:28:09 by ekrebs            #+#    #+#             */
/*   Updated: 2025/02/16 21:35:31 by ekrebs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "memory_manager.h"
#include "mm_interns.h"

/**
 * @brief 
 * 
 * could be upgraded later if allocations are slow (as they parcour the linked list left to right,)
 * could be upgraded with an int to the structu, signifying the nb of added elements, to directly add new of to the end.
 * 
 * @param mm 
 * @param area 
 * @param elem 
 */
void	mm_area_add_elem(t_mm *mm, char *area, void *elem)
{
	t_area_node		*area_node;

	area_node = go_to_area_name(mm, area);
	mm_hashmap_add(mm, area_node->area_hashmap, elem);
	return ;
}

void	mm_area_free_elem(t_mm *mm, char *area, void *elem)
{
	t_area_node		*area_node;

	area_node = go_to_area_name(mm, area);
	mm_hashmap_remove(mm, area_node->area_hashmap, elem);
	return ;
}
