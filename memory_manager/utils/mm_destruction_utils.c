/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mm_destruction_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekrebs <ekrebs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 21:13:15 by ekrebs            #+#    #+#             */
/*   Updated: 2025/02/16 22:41:11 by ekrebs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "memory_manager.h"
#include "../mm_interns.h"

void	destroy_content_array(t_content_array *content)
{
	size_t	i;
	size_t	size;

	size = sizeof(content->bits);
	i = 0;
	while(i < size)
	{
		if (content->bits[i])
			free(content->content[i]);
		i++;
	}
	free(content->content);
	free(content->bits);
	free(content);
	return ;
}

void	destroy_area_hahsmap(t_content_hashmap *hashmap)
{
	size_t				i;
	size_t				size;

	i = 0;
	while (i < MM_HASHMAP_NB_BUCKETS)
	{
		destroy_content_array(&hashmap->buckets[i]);
		i++;
	}
	return ;
}

void	destroy_area(t_area_node *area)
{
	free(area->area_name);
	destroy_area_hahsmap(&area->area_hashmap);
	free(area);
	return ;
}

void	destroy_areas(t_area_node *areas)
{
	t_area_node	*next;

	while(areas)
	{
		next = areas->next;
		destroy_area(areas);
		areas = next;
	}
	return ;
}