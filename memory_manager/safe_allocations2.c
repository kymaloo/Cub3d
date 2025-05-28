/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_allocations2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekrebs <ekrebs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 20:58:08 by ekrebs            #+#    #+#             */
/*   Updated: 2025/05/28 20:58:56 by ekrebs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

char	*safe_substr(char *area, const char *str, \
												unsigned int start, size_t len)
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
