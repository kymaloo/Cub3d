
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

#endif