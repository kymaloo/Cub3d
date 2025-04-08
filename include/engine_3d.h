
#ifndef ENGINE_3D_H
# define ENGINE_3D_H

# include "struct.h"

# define SCREEN_WIDTH	1280
# define SCREEN_HEIGHT	720

# define MAP_SQUARE_SIDE_X		32
# define MAP_SQUARE_SIDE_Y		32
# define RENDER_DISTANCE		10000

# define PLAYER_HALF_THICKNESS	5
# define WALL_WIDTH				64
# define WALL_HEIGHT			64

#ifdef M_PI
	#undef M_PI
#endif
#define M_PI 3.14159

typedef	struct s_map t_map;

enum e_coords
{
	X = 0,
	Y,
	NB_DIM,
};

typedef enum e_collision_type
{
	FLOOR,
	RAYHIT_WALL_SOUTH,
	RAYHIT_WALL_NORTH,
	RAYHIT_WALL_EAST,
	RAYHIT_WALL_WEST
} t_wall_collision_type;

typedef struct s_camera
{
	float	start[NB_DIM];
	float	end[NB_DIM];
	float	camera_length;
	float	camera_step[NB_DIM];
} t_camera;

typedef struct s_ray_infos 
{
	float					point[NB_DIM];
	float					angle;
	float					dist;
	enum e_coords			axis_of_collision;
	enum e_collision_type	type_collided;
} t_ray_infos, t_ray;

typedef struct s_player
{
	char		facing;
	float		position[NB_DIM];
	t_camera	camera;
	float		angle;
}	t_player;

typedef struct s_digital_differential_analyser 
{
	float	cos_a;
	float	sin_a;
	float	recipCos_a;
	float	recipSin_a;
	t_map	*map;
	float	dist_walked_x;
	float	dist_walked_y;
	float	step_x;
	float	step_y;

	float 	step_sign[NB_DIM];
	float	first_step_x;
	float	first_step_y;
} t_digital_differential_analyser, t_dda;

void	init_coords(int *coords, int x, int y);
void	rotate_vector(float *v, float angle_rad);

#endif