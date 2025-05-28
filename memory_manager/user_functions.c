/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekrebs <ekrebs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 11:27:09 by ekrebs            #+#    #+#             */
/*   Updated: 2025/05/28 20:46:10 by ekrebs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils/mm_interns.h"

void	nuclear_exit(int err_code)
{
	memory_manager(MM_NUKE, NULL, &err_code);
}

void	memory_manager_area_create(char *area_name, \
					t_deletion_func	deletion_func, size_t nb_hahsmap_buckets)
{
	t_area_create_data	a;

	a.deletion_func = deletion_func;
	a.nb_hahsmap_buckets = nb_hahsmap_buckets;
	memory_manager(MM_AREA_CREATE, area_name, &a);
}

void	memory_manager(t_mm_opcode opcode, char *area_name, void *data)
{
	static t_mm	*mm = NULL;

	if (opcode == CREATE)
		mm_create(&mm);
	else if (opcode == DESTROY)
		mm_destroy(mm);
	else if (opcode == MM_AREA_CREATE)
		mm_area_create(mm, area_name, ((t_area_create_data *) data));
	else if (opcode == AREA_DELETE)
		mm_area_delete(mm, area_name);
	else if (opcode == ADD_ELEM)
		mm_area_add_elem(mm, area_name, data);
	else if (opcode == DEL_ELEM)
		mm_area_free_elem(mm, area_name, data);
	else if (opcode == MM_NUKE)
		mm_nuclear_exit(mm, *((int *) data));
	else
		mm_nuclear_exit(NULL, ft_error(WHERE, "Unknown opcode", EXIT_FAILURE));
	return ;
}
