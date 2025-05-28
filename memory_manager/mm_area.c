/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mm_area.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekrebs <ekrebs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 21:21:06 by ekrebs            #+#    #+#             */
/*   Updated: 2025/05/28 11:27:03 by ekrebs           ###   ########.fr       */
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
void	mm_area_create(t_mm *mm, char *area_name, t_area_create_data *a)
{
	t_area_node	*area_node;

	if (!a->deletion_func)
		mm_nuclear_exit(mm, ft_error(WHERE, "no deletion function", EXIT_FAILURE));
	else if (a->nb_hahsmap_buckets < 1)
		mm_nuclear_exit(mm, ft_error(WHERE, "invalid hashmap buckets number", EXIT_FAILURE));
	else if (!mm->areas)
	{
		mm->areas = create_area_node(mm, area_name, a->deletion_func, a->nb_hahsmap_buckets);
		return ;
	}
	area_node = mm->areas;
	while (area_node->next)
		area_node = area_node->next;
	area_node->next = create_area_node(mm, area_name, a->deletion_func, a->nb_hahsmap_buckets);
	if (!area_node)
		mm_nuclear_exit(mm, EXIT_FAILURE);
	return ;
}

void	mm_area_delete(t_mm *mm, char *area_name_to_delete)
{
	t_area_node	*area_node;
	t_area_node	*killme;

	area_node = mm->areas;
	if (ft_strcmp(mm->areas->area_name, area_name_to_delete) == EXIT_SUCCESS)
	{
		mm->areas = mm->areas->next;
		destroy_area(area_node);
		return ;
	}
	while (area_node->next)
	{
		if (ft_strcmp(area_node->next->area_name, area_name_to_delete) == EXIT_SUCCESS)
		{
			killme = area_node->next;
			area_node->next = area_node->next->next;
			destroy_area(killme);
			return ;
		}
		area_node = area_node->next;
	}
	return ;
}
