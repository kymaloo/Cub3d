
#ifndef ENGINE_3D_H
# define ENGINE_3D_H

# define DISPLAY_X_MAX	1280
# define DISPLAY_Y_MAX	720

enum e_coord
{
	X = 0,
	Y = 1,
};

typedef	struct s_vect2D
{
	double coords[2]
}	t_vect2D, t_vect;

typedef struct s_player
{
	t_vect2D	position;
	t_vect2D	direction;
	t_vect2D	plane;
}	t_player;

typedef struct s_ray
{
	t_vect2D	position;
	t_vect2D	direction;
}	t_ray;

#endif