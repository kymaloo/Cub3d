
#include "memory_manager.h"

void	*safe_malloc(t_mm *mm, char *area, size_t size)
{
	void	*new;

	new = malloc(size);
	mm_area_add_elem(mm, area, new);
	return (new);
}


void	*safe_calloc(t_mm *mm, char *area, size_t nmeb, size_t size)
{
	void	*new;

	new = ft_calloc(nmeb, size);
	mm_area_add_elem(mm, area, new);
	return (new);
}

char	*safe_strdup(t_mm *mm, char *area, const char str)
{
	void	*new;

	new = ft_strdup(str);
	mm_area_add_elem(mm, area, new);
	return (new);
}
