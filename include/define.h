#ifndef DEFINE_H
# define DEFINE_H

# define MALLOC_FAILED		"Error: Malloc failed\n"

# define ZONE_1				"petit_chacalot"
# define ZONE_MLX			"zebi_la_mlx"
# define ZONE_FDS			"oulah_les_Fds"
# define WIDTH				1920
# define HEIGHT				1080
# define FOV				70
# define PI					3.1415

# define C_WALL_NORTH		0x000000FF
# define C_WALL_SOUTH		0x000000FF
# define C_WALL_EAST		0x000000FF
# define C_WALL_WEST		0x000000FF

# define C_INVALID			0xD3D3D3FF
# define C_WHITE			0xFFFFFFFF

# define FLOOR				0
# define CEILING			1

enum e_error
{
	MALLOC_ERROR = -1,
	EXIT_SUCCESS,
	EXIT_FAILURE,
	DIRECTION,
	FC,
};

#endif