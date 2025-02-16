/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mm_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekrebs <ekrebs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 21:13:12 by ekrebs            #+#    #+#             */
/*   Updated: 2025/02/17 00:03:13 by ekrebs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "memory_manager.h"
#include "../mm_interns.h"

t_area_node	*go_to_area_name(t_mm *mm, char *area_name_to_find)
{
	t_area_node	*area_node;
	t_area_node	*next;

	area_node = mm->areas;
	while(area_node)
	{
		next = area_node->next;
		if (strcmp(area_node->area_name, area_name_to_find) == EXIT_SUCCESS)
			return (area_node);
		area_node = next;
	}
	mm_nuclear_exit(mm, error(WHERE, "not a valid area name", EXIT_FAILURE));
	return (NULL);
}

t_content_array *initialize_content_array(t_mm *mm, t_content_array *new)
{
	if (!new)
		mm_nuclear_exit(mm, error(WHERE, "failure.", EXIT_FAILURE));
	new->content = ft_calloc(MM_INITIAL_CONTENT_NB, MM_INITIAL_CONTENT_NB * sizeof(void *));
	if (!new->content)
		mm_nuclear_exit(mm, error(WHERE, "calloc failure.", EXIT_FAILURE));
	new->bits = ft_calloc(MM_INITIAL_CONTENT_NB, MM_INITIAL_CONTENT_NB * 1);
	if (!new->bits)
		mm_nuclear_exit(mm, error(WHERE, "calloc failure.", EXIT_FAILURE));
	new->bitfield_size = MM_INITIAL_CONTENT_NB;
	return (new);
}

void upgrade_content_array_size(t_mm *mm, t_content_array *old)
{
	bool	*new_bits;
	void	*new_content;
	size_t	old_size;
	size_t	new_size;

	old_size = old->bitfield_size; 
	new_size = old_size * 2;
	new_content = ft_calloc(new_size, new_size * sizeof(void *));
	if (!new_content)
		mm_nuclear_exit(mm, error(WHERE, "calloc failure.", EXIT_FAILURE));
	ft_memcpy(new_content, old->content, old_size * sizeof(void *));
	free(old->content);
	old->content = new_content;
	new_bits = ft_calloc(new_size, new_size);
	if (!new_bits)
		mm_nuclear_exit(mm, error(WHERE, "calloc failure.", EXIT_FAILURE));
	ft_memcpy(new_bits, old->bits, old_size);
	free(old->bits);
	old->bits = new_bits;
	old->bitfield_size = new_size;
	return ;
}

t_area_node	*create_area_node(t_mm *mm, char *new_area_name)
{
	t_area_node	*new;
	size_t		i;

	i = ft_strlen(new_area_name);
	if (i > MM_AREA_NAME_MAX_SIZE || i <= 0)
		mm_nuclear_exit(mm, error(WHERE, "bad name size.", EXIT_FAILURE));
	new = malloc(sizeof(t_area_node));
	if (!new)
		mm_nuclear_exit(mm, error(WHERE, "malloc failure.", EXIT_FAILURE));
	new->area_name = ft_strdup(new_area_name);
	if (!new->area_name)
		mm_nuclear_exit(mm, error(WHERE, "malloc failure.", EXIT_FAILURE));
	i = 0;
	while (i < MM_HASHMAP_NB_BUCKETS)
	{
		initialize_content_array(mm, &new->area_hashmap.buckets[i]);
		i++;
	}
	new->next = NULL;
	return (new);
}
