/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_allocations.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekrebs <ekrebs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 11:25:39 by ekrebs            #+#    #+#             */
/*   Updated: 2025/05/28 11:28:22 by ekrebs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "memory_manager.h"
#include "cub.h"

void	*safe_malloc(char *area, size_t size)
{
	void	*new;

	new = malloc(size);
	if (!new)
		nuclear_exit(ft_error(WHERE, "malloc failure", MALLOC_ERROR));
	memory_manager(ADD_ELEM, area, new);
	return (new);
}

void	*safe_calloc(char *area, size_t nmeb, size_t size)
{
	void	*new;

	new = ft_calloc(nmeb, size);
	if (!new)
		nuclear_exit(ft_error(WHERE, "malloc failure", MALLOC_ERROR));
	memory_manager(ADD_ELEM, area, new);
	return (new);
}

char	*safe_strdup(char *area, const char *str)
{
	void	*new;

	new = ft_strdup(str);
	if (!new)
		nuclear_exit(ft_error(WHERE, "malloc failure", MALLOC_ERROR));
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

char	*safe_substr(char *area, const char *str, unsigned int start, size_t len)
{
	void	*new;

	new = ft_substr(str, start, len);
	if (!new)
		nuclear_exit(ft_error(WHERE, "malloc failure", MALLOC_ERROR));
	memory_manager(ADD_ELEM, area, new);
	return (new);
}

char	**safe_split(char *area, const char *s, char c)
{
	int			nbword;
	char		**tab;
	const char	*start;
	int			i;

	i = 0;
	if (!s)
		return (NULL);
	nbword = ft_count_word(s, c);
	tab = safe_malloc(area, (sizeof(char *) * (nbword + 1)));
	if (!tab)
		nuclear_exit(ft_error(WHERE, "malloc failure", MALLOC_ERROR));
	while (i < nbword)
	{
		while (*s && *s == c)
			s++;
		start = s;
		while (*s && *s != c)
			s++;
		tab[i] = safe_substr(area, start, 0, s - start);
		if (!tab[i++])
			nuclear_exit(ft_error(WHERE, "substr failure", MALLOC_ERROR));
	}
	tab[i] = NULL;
	return (tab);
}

char	*safe_strdup_with_calloc(char *area, char *str, int size)
{
	void	*new;

	new = ft_strdup_with_calloc(str, size);
	if (!new)
		nuclear_exit(ft_error(WHERE, "strdup failure", MALLOC_ERROR));
	memory_manager(ADD_ELEM, area, new);
	return (new);
}
