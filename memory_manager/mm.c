/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekrebs <ekrebs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 15:55:19 by ekrebs            #+#    #+#             */
/*   Updated: 2025/05/29 13:47:41 by ekrebs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils/mm_interns.h"

void	mm_create(t_mm **mm)
{
	if (*mm)
		mm_nuclear_exit(NULL, ft_error(__FILE__":", __LINE__, \
								"mm_create(): mm isn't NULL", EXIT_FAILURE));
	*mm = malloc(sizeof(t_mm));
	if (!*mm)
		mm_nuclear_exit(NULL, ft_error(__FILE__":", __LINE__, \
								"mm_create(): malloc failure", EXIT_FAILURE));
	(*mm)->areas = NULL;
}

void	mm_destroy(t_mm *mm)
{
	destroy_areas(mm->areas);
	free(mm);
}

void	mm_nuclear_exit(t_mm *mm, t_status status)
{
	mm_destroy(mm);
	exit(status);
}
