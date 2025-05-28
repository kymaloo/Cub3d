/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mm_destruction_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekrebs <ekrebs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 21:13:15 by ekrebs            #+#    #+#             */
/*   Updated: 2025/05/28 20:48:43 by ekrebs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mm_interns.h"

void	destroy_content_array(t_content_array *content, \
												t_deletion_func deletion_func)
{
	size_t	i;
	size_t	size;

	size = content->size;
	i = 0;
	while (i < size)
	{
		if (content->bits[i])
			deletion_func(content->content[i]);
		i++;
	}
	free(content->content);
	free(content->bits);
	return ;
}

void	destroy_area_hahsmap_content_array(t_content_hashmap *hashmap, \
												t_deletion_func deletion_func)
{
	size_t				i;

	i = 0;
	while (i < hashmap->nb_buckets)
	{
		destroy_content_array(&hashmap->buckets[i], deletion_func);
		i++;
	}
	free(hashmap->buckets);
	return ;
}

void	destroy_area(t_area_node *area)
{
	free(area->area_name);
	destroy_area_hahsmap_content_array(&area->area_hashmap, \
														area->deletion_func);
	free(area);
	return ;
}

void	destroy_areas(t_area_node *areas)
{
	t_area_node	*next;

	while (areas)
	{
		next = areas->next;
		destroy_area(areas);
		areas = next;
	}
	return ;
}
