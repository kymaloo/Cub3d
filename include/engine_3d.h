
#ifndef ENGINE_3D_H
# define ENGINE_3D_H

# define SCREEN_WIDTH	1280
# define SCREEN_HEIGHT	720

# define MAP_SQUARE_SIDE_X		32
# define MAP_SQUARE_SIDE_Y		32
# define RENDER_DISTANCE		10000

# define PLAYER_HALF_THICKNESS	5
# define WALL_WIDTH				64
# define WALL_HEIGHT			64

enum e_coord
{
	X = 0,
	Y,
	NB_DIM,
};

typedef struct s_camera
{
	double	start[NB_DIM];
	double	end[NB_DIM];
	double	camera_length;
	double	camera_step[NB_DIM];
} t_camera;

typedef struct s_ray_infos 
{
	double	point[NB_DIM];
	double	angle;
	double	dist;
	int		collision_type;
} t_ray_infos, t_ray;

typedef struct s_digital_differential_analyser 
{
	double	dist_walked_x;
	double	dist_walked_y;
	double	step_x;
	double	step_y;
	double	recipCos_a;
	double	recipSin_a;
	double	cos_a;
	double	sin_a;
} t_digital_differential_analyser, t_dda;

void	init_coords(int *coords, int x, int y);
void	rotate_vector(double *v, double angle_rad);

#endif