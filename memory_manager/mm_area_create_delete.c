/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mm_area_create_delete.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekrebs <ekrebs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 17:28:02 by ekrebs            #+#    #+#             */
/*   Updated: 2025/02/13 20:03:20 by ekrebs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "memory_manager.h"

t_content_node	*create_content_node()
{
	t_content_node	*new;
	size_t			i;

	new = malloc(sizeof(t_content_node));
	if (!new)
		return NULL;
	i = 0;
	while(i < MM_AREA_NODE_CONTENT_NB)
		new->content[i++] = NULL;
	new->next = NULL;
	return (new);
}

t_area_node	*create_area_node(char *new_area_name)
{
	t_area_node	*new;
	size_t		name_size;

	new = malloc(sizeof(t_content_node));
	if (!new)
		return (NULL);
	name_size = ft_strlen(new_area_name);
	if (name_size > MM_AREA_NAME_MAX_SIZE || name_size <= 0);
		return (free(new), error(WHERE, "bad new area name", \
														EXIT_FAILURE), NULL);
	ft_strlcpy(new_area_name, new->area_name, name_size);
	new->area_content = create_content_node();
	if (!new->area_content)
		return (free(new), NULL);
	new->next = NULL;
	return (new);
}

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
	t_area_node		*area_node;

	area_node = mm->areas;
	while(area_node)
		area_node = area_node->next;
	area_node = create_area_node(new_area_name);
	if (!area_node)
		mm_nuclear_exit(mm, EXIT_FAILURE);
	area_node->area_content = create_content_node();
	if (!area_node->area_content)
		mm_nuclear_exit(mm, error(WHERE, "mm_area_create: malloc failure.", EXIT_FAILURE));
}
void	mm_area_delete(t_mm *mm, char *area_name_to_delete)
{

}