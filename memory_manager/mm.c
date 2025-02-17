/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekrebs <ekrebs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 15:55:19 by ekrebs            #+#    #+#             */
/*   Updated: 2025/02/17 13:46:13 by ekrebs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils/mm_interns.h"

t_mm	*mm_create(void)
{
	t_mm 	*new;

	new = malloc(sizeof(t_mm));
	if (!new)
		mm_nuclear_exit(NULL, ft_error(WHERE, "mm_create(): malloc failure", EXIT_FAILURE));
	new->areas = NULL;
	return (new);
}

void	mm_destroy(t_mm *mm)
{
	destroy_areas(mm->areas);
	free(mm);
	return ;
}

void	mm_nuclear_exit(t_mm *mm, t_status status)
{
	mm_destroy(mm);
	exit(status);
}