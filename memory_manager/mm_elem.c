/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mm_elem.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekrebs <ekrebs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 19:28:09 by ekrebs            #+#    #+#             */
/*   Updated: 2025/05/29 13:53:10 by ekrebs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils/mm_interns.h"

/**
 * @brief 
 * 
 * could be upgraded later if allocations are slow 
 * (as they parcour the linked list left to right,)
 * could be upgraded with an int to the structu, 
 * signifying the nb of added elements, to directly add new of to the end.
 * 
 * @param mm 
 * @param area 
 * @param elem 
 */
void	mm_area_add_elem(t_mm *mm, char *area, void *elem)
{
	t_area_node		*area_node;

	if (!elem)
		mm_nuclear_exit(mm, ft_error(__FILE__":", __LINE__, \
											"element is NULL", EXIT_FAILURE));
	area_node = go_to_area_name(mm, area);
	mm_hashmap_add(mm, &area_node->area_hashmap, elem);
	return ;
}

void	mm_area_free_elem(t_mm *mm, char *area, void *elem)
{
	t_area_node		*area_node;

	if (!elem)
		mm_nuclear_exit(mm, ft_error(__FILE__":", __LINE__, \
							"element is NULL (how dare you)", EXIT_FAILURE));
	area_node = go_to_area_name(mm, area);
	mm_hashmap_remove(mm, &area_node->area_hashmap, elem);
	return ;
}
