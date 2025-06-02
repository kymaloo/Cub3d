/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_allocations2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekrebs <ekrebs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 20:58:08 by ekrebs            #+#    #+#             */
/*   Updated: 2025/05/29 14:02:42 by ekrebs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

char	*safe_substr(char *area, const char *str, \
												unsigned int start, size_t len)
{
	void	*new;

	new = ft_substr(str, start, len);
	if (!new)
		nuclear_exit(ft_error(__FILE__":", __LINE__, \
											"malloc failure", MALLOC_ERROR));
	memory_manager(ADD_ELEM, area, new);
	return (new);
}

char	**safe_split(char *area, const char *s, char c)
{
	struct s_safe_split_data	sp;

	sp.i = 0;
	if (!s)
		return (NULL);
	sp.nbword = ft_count_word(s, c);
	sp.tab = safe_malloc(area, (sizeof(char *) * (sp.nbword + 1)));
	if (!sp.tab)
		nuclear_exit(ft_error(__FILE__":", __LINE__, \
											"malloc failure", MALLOC_ERROR));
	while (sp.i < sp.nbword)
	{
		while (*s && *s == c)
			s++;
		sp.start = s;
		while (*s && *s != c)
			s++;
		sp.tab[sp.i] = safe_substr(area, sp.start, 0, s - sp.start);
		if (!sp.tab[sp.i++])
			nuclear_exit(ft_error(__FILE__":", __LINE__, \
											"substr failure", MALLOC_ERROR));
	}
	sp.tab[sp.i] = NULL;
	return (sp.tab);
}

char	*safe_strdup_with_calloc(char *area, char *str, int size)
{
	void	*new;

	new = ft_strdup_with_calloc(str, size);
	if (!new)
		nuclear_exit(ft_error(__FILE__":", __LINE__, \
											"strdup failure", MALLOC_ERROR));
	memory_manager(ADD_ELEM, area, new);
	return (new);
}
