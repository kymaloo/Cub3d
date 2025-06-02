/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_allocations.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekrebs <ekrebs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 11:25:39 by ekrebs            #+#    #+#             */
/*   Updated: 2025/05/29 13:55:19 by ekrebs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "memory_manager.h"
#include "cub.h"

void	*safe_malloc(char *area, size_t size)
{
	void	*new;

	new = malloc(size);
	if (!new)
		nuclear_exit(ft_error(__FILE__":", __LINE__, \
											"malloc failure", MALLOC_ERROR));
	memory_manager(ADD_ELEM, area, new);
	return (new);
}

void	*safe_calloc(char *area, size_t nmeb, size_t size)
{
	void	*new;

	new = ft_calloc(nmeb, size);
	if (!new)
		nuclear_exit(ft_error(__FILE__":", __LINE__, \
											"malloc failure", MALLOC_ERROR));
	memory_manager(ADD_ELEM, area, new);
	return (new);
}

char	*safe_strdup(char *area, const char *str)
{
	void	*new;

	new = ft_strdup(str);
	if (!new)
		nuclear_exit(ft_error(__FILE__":", __LINE__, \
											"malloc failure", MALLOC_ERROR));
	memory_manager(ADD_ELEM, area, new);
	return (new);
}

char	*safe_get_next_line(char *area, int fd)
{
	char	*line;

	line = get_next_line(fd);
	if (line)
		memory_manager(ADD_ELEM, area, line);
	return (line);
}

void	safe_free(char *area, void *address)
{
	memory_manager(DEL_ELEM, area, address);
}
