#include "../include/cub.h"

int	main(int argc, char **argv)
{
	t_mm			*mm;
	t_parsing_map	*map;

	if (argc != 2)
		return (ft_error(WHERE, "Bad argument", EXIT_FAILURE));

	mm = mm_create();
	mm_area_create(mm, ZONE_1);

	map = safe_calloc(mm, ZONE_1, 1, sizeof(t_parsing_map));
	mm_area_create(mm, ZONE_PARSING_TMP);
	if (init(mm, map, argv[1]) != EXIT_SUCCESS)
		mm_nuclear_exit(mm, ft_error(WHERE, "init() failure", EXIT_FAILURE));
	mm_area_delete(mm, ZONE_PARSING_TMP);
	mm_destroy(mm);
	return (EXIT_SUCCESS);
}
