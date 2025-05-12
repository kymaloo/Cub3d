#ifndef DEFINE_H
# define DEFINE_H

# define MALLOC_FAILED		"Error: Malloc failed\n"

# define ZONE_PARSE				"petit_chacalot"
# define ZONE_MLX			"zebi_la_mlx"
# define ZONE_FDS			"oulah_les_Fds"

# define WIDTH				1920
# define HEIGHT				1080

# define FOV				70

# define M_PI				3.14159265358979323846

# define C_WALL_BLACK		0x000000FF
# define C__FLOOR_BROWN		0x4B3A26FF
# define C_BLUE				0x0000FFFF
# define C_WHITE			0xFFFFFFFF
# define C_GREY_INVALID		0xD3D3D3FF

# define DIM	2

enum e_coord
{
	X = 0,
	Y = 1,
};


enum e_error
{
	MALLOC_ERROR = -1,
	EXIT_SUCCESS,
	EXIT_FAILURE,
	DIRECTION,
	FC,
};

#endif