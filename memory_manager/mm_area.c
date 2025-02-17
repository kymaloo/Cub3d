/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mm_area.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekrebs <ekrebs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 21:21:06 by ekrebs            #+#    #+#             */
/*   Updated: 2025/02/17 13:31:15 by ekrebs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils/mm_interns.h"

/**
 * @brief creates an area of the mm
 * 
 * exits with nuclear exit on failure.
 * 
 * @param mm
 * @param new_area_name 
 */
void	mm_area_create(t_mm *mm, char *new_area_name)
{
	t_area_node	*area_node;

	area_node = mm->areas;
	while(area_node)
		area_node = area_node->next;
	area_node = create_area_node(mm, new_area_name);
	if (!area_node)
		mm_nuclear_exit(mm, EXIT_FAILURE);
	return ;
}

void	mm_area_delete(t_mm *mm, char *area_name_to_delete)
{
	t_area_node	*area_node;

	area_node = go_to_area_name(mm, area_name_to_delete);
	destroy_area(area_node);
	return ;
}