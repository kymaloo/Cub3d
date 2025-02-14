/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mm_content_elements.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekrebs <ekrebs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 19:28:09 by ekrebs            #+#    #+#             */
/*   Updated: 2025/02/14 19:42:28 by ekrebs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "memory_manager.h"

void	mm_area_add_elem(t_mm *mm, char *area, void *elem)
{
	t_area_node		*area_node;
	t_content_node	*content_node;
	t_content_node	*next;
	size_t			i;

	area_node = go_to_area_name(mm, area);
	content_node = area_node->area_content;
	while(content_node)
	{
		next = content_node->next;
		i = 0;
		while(i < MM_AREA_NODE_CONTENT_NB)
		{
			if (content_node->content[i] == NULL)
			{
				content_node->content[i] = elem;
				return ;
			}
		}
		content_node = next;
	}
	next = create_content_node(mm);
	next->content[0] = elem;
	return ;
}

void	mm_area_free_elem(t_mm *mm, char *area, void *elem)
{
	t_area_node		*area_node;
	t_content_node	*content_node;
	t_content_node	*next;
	size_t			i;

	area_node = go_to_area_name(mm, area);
	content_node = area_node->area_content;
	while(content_node)
	{
		next = content_node->next;
		i = 0;
		while(i < MM_AREA_NODE_CONTENT_NB)
		{
			if (content_node->content[i] == elem)
			{
				free(content_node->content[i]);
				content_node->content[i] = NULL;
				return ;
			}
		}
		content_node = next;
	}
	mm_nuclear_exit(mm, error(WHERE, "elem not found.", EXIT_FAILURE));
}
