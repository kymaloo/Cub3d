
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
