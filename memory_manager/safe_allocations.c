
#include "memory_manager.h"

void	*safe_malloc(t_mm *mm, char *area, size_t size)
{
	void	*new;

	new = malloc(size);
	if (!new)
		mm_nuclear_exit(mm, ft_error(WHERE, "malloc failure", MALLOC_ERROR));
	mm_area_add_elem(mm, area, new);
	return (new);
}


void	*safe_calloc(t_mm *mm, char *area, size_t nmeb, size_t size)
{
	void	*new;

	new = ft_calloc(nmeb, size);
	if (!new)
		mm_nuclear_exit(mm, ft_error(WHERE, "malloc failure", MALLOC_ERROR));
	mm_area_add_elem(mm, area, new);
	return (new);
}

char	*safe_strdup(t_mm *mm, char *area, const char *str)
{
	void	*new;

	new = ft_strdup(str);
	if (!new)
		mm_nuclear_exit(mm, ft_error(WHERE, "malloc failure", MALLOC_ERROR));
	mm_area_add_elem(mm, area, new);
	return (new);
}

char	*safe_get_next_line(t_mm *mm, char *area, int fd)
{
	char	*line;

	line = get_next_line(fd);
	if (line)
		mm_area_add_elem(mm, area, line);
	return (line);
}

void	safe_free(t_mm *mm, char *area, void *address)
{
	mm_area_free_elem(mm, area, address);
}

char	*safe_substr(t_mm *mm, char *area, const char *str, unsigned int start, size_t len)
{
	void	*new;

	new = ft_substr(str, start, len);
	if (!new)
		mm_nuclear_exit(mm, ft_error(WHERE, "malloc failure", MALLOC_ERROR));
	mm_area_add_elem(mm, area, new);
	return (new);
}

char	**safe_split(t_mm *mm, char *area, const char *s, char c)
{
	int			nbword;
	char		**tab;
	const char	*start;
	int			i;

	i = 0;
	if (!s)
		return (NULL);
	nbword = ft_count_word(s, c);
	tab = safe_malloc(mm, area, (sizeof(char *) * (nbword + 1)));
	if (!tab)
		mm_nuclear_exit(mm, ft_error(WHERE, "malloc failure", MALLOC_ERROR));
	while (i < nbword)
	{
		while (*s && *s == c)
			s++;
		start = s;
		while (*s && *s != c)
			s++;
		tab[i] = safe_substr(mm, area, start, 0, s - start);
		if (!tab[i++])
			mm_nuclear_exit(mm, ft_error(WHERE, "substr failure", MALLOC_ERROR));
	}
	tab[i] = NULL;
	return (tab);
}

char	*safe_strdup_with_calloc(t_mm *mm, char *area, char *str, int size)
{
	void	*new;

	new = ft_strdup_with_calloc(str, size);
	if (!new)
		mm_nuclear_exit(mm, ft_error(WHERE, "malloc failure", MALLOC_ERROR));
	mm_area_add_elem(mm, area, new);
	return (new);
}
