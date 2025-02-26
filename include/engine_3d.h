
#ifndef ENGINE_3D_H
# define ENGINE_3D_H

# define SCREEN_WIDTH	1280
# define SCREEN_HEIGHT	720


# define DIM	2
enum e_coord
{
	X = 0,
	Y = 1,
};

typedef struct s_ray
{
	double	position[DIM];
	double	direction[DIM];
}	t_ray;

void	init_coords(int *coords, int x, int y);
void	rotate_vector(double *v, double angle_rad);

#endif