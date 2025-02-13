/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mm_create_destory.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekrebs <ekrebs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 15:55:19 by ekrebs            #+#    #+#             */
/*   Updated: 2025/02/13 19:45:13 by ekrebs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "memory_manager.h"

t_mm	*mm_create(void)
{
	t_mm *new;
	size_t	i;

	new = malloc(sizeof(t_mm));
	if (!new)
		mm_nuclear_exit(NULL, "mm_create(): malloc failure", EXIT_FAILURE);
	new->areas = NULL;
	return (new);
}

void	destroy_area_content(t_content_node *content_node)
{
	t_area_node	*next;
	size_t		i;

	while(content_node)
	{
		next = content_node->next;
		i = 0;
		while(i < MM_AREA_NODE_CONTENT_NB)
		{
			if (content_node->content[i]) 
				free(content_node->content[i]);
			i++;
		}
		free(content_node);
		content_node = next;
	}
}

void	destroy_areas(t_area_node *areas)
{
	t_area_node	*next;

	while(areas)
	{
		next = areas->next;
		destroy_area_content(areas->area_content);
		free(areas);
		areas = next;
	}
}

void	mm_destroy(t_mm *mm)
{
	size_t	i;

	i = 0;
	destroy_areas(mm->areas);
	free(mm);
	return ;
}