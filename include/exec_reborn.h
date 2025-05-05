#ifndef EXEC_REBORN_H
# define EXEC_REBORN_H

# include <stdio.h>
# include <fcntl.h>
# include <stdbool.h>
# include <math.h>
# include <sys/time.h>
# include "memory_manager.h"
# include "ainsi_color_codes.h"
# include "parsing.h"

# define TILE_SIZE 64.0f
# define MAX_RENDER_DISTANCE (100 * TILE_SIZE)  // Render distance = 100 tiles
# define SCREEN_WIDTH 1280
# define SCREEN_HEIGHT 720

# define COLOR_MISSING 0xFF00FFFF


/**
 * @enum e_wall_direction
 * @brief Defines possible wall orientations for texturing
 */
typedef enum e_wall_direction {
	NORTH,  // North-facing wall
    SOUTH,  // South-facing wall
    EAST,   // East-facing wall
    WEST,   // West-facing wall
    NO_COLLISION  // No collision detected
} t_wall_direction;

/**
 * @struct s_collision_infos
 * @brief Stores ray collision information
 */
typedef struct s_collision_infos {
	float wall_distance;      // Distance to wall in world units
    t_wall_direction face;   // Wall face that was hit
    float wall_hit_pos;      // Relative wall hit position [0-1]
} t_collision_infos;

/**
 * @struct s_dda
 * @brief Contains state of an active DDA algorithm
 */
typedef struct s_dda {
    float ray_dir_x;         // Normalized ray X direction
    float ray_dir_y;         // Normalized ray Y direction
    float delta_dist_x;      // Distance between X-axis intersections
    float delta_dist_y;      // Distance between Y-axis intersections
    float side_dist_x;       // Distance to next X-axis intersection
    float side_dist_y;       // Distance to next Y-axis intersection
    int step_x;              // X increment (-1 or 1)
    int step_y;              // Y increment (-1 or 1)
    int map_current_x;       // Current X position in grid
    int map_current_y;       // Current Y position in grid
    int side;                // Intersection type (0=vertical, 1=horizontal)
} t_dda;

typedef	struct s_time
{
	struct timeval	now;
	struct timeval	old;
	suseconds_t		time_taken_to_draw_frame;
}	t_time;

typedef struct s_images
{
	mlx_image_t	*background;
	mlx_image_t	*walls;
	mlx_image_t	*minimap;
	mlx_image_t	*minimap_player;
	mlx_image_t	*radar;
} t_images;

typedef	struct s_colors
{
	char	*color_floor;	//your sotred the str you read
	char	*color_ceiling;	//your sotred the str you read

	uint32_t	color_floor_uint;	//fill me up with the actual represented color using RGBA
	uint32_t	color_ceiling_uint; //fill me up with the actual represented color using RGBA
}	t_colors;

typedef struct s_textures
{
	mlx_texture_t	*minimap_player;
	mlx_texture_t	*wall_north;
	mlx_texture_t	*wall_south;
	mlx_texture_t	*wall_east;
	mlx_texture_t	*wall_west;
} t_textures;

typedef struct s_paths
{
	char	*minimap_player;
	char	*wall_north;
	char	*wall_south;
	char	*wall_east;
	char	*wall_west;
} t_paths;

typedef struct s_mlx_infos
{
	mlx_t			*mlx;
	t_images		images;
	t_textures		textures;
	t_colors		colors;
	t_paths			paths;
} t_mlx_infos;

typedef	struct s_map
{
	char	**map;
	int		x_max;
	int		y_max;
	int		tile_size;
}	t_map;




//TODO fixme

typedef struct s_camera {
    float	dir_x;        // Vecteur direction (normalisé)
    float	dir_y;
    float	plane_x;      // Plan de la caméra (pour FOV)
    float	plane_y;
    float	fov;         // Champ de vision en radians
} t_camera;

typedef struct s_player {
	char	facing;
    float	x;            // Position x dans le monde
    float	y;            // Position y dans le monde
    float	move_speed;   // Vitesse de déplacement
    float	rot_speed;    // Vitesse de rotation
    t_camera camera;    // Camera attachée au joueur
} t_player;

/*typedef struct s_player
{
	char		facing;
	float		position[NB_DIM];
	t_camera	camera;
	float		angle;
}	t_player;*/

typedef struct s_game
{
	t_player	player;
	t_map		map;
	t_mlx_infos	mlx_infos;
	t_collision_infos ray_collisions[SCREEN_WIDTH];
	t_time		time;
} t_game;

typedef struct s_infos_p
{
	t_parsing_map	*p;
	t_game			*g;
} t_infos_p;

void	render_frame(t_game *g, t_mlx_infos *m, t_textures *t, t_collision_infos *c);


void	raycast(t_game *g, t_player *player, t_collision_infos *collisions);


void	player_rotations(t_game *g);
void	player_moves(t_game *g);
void	keys_pressed();

void	advance_dda(t_dda *dda);
int		check_collision(t_game *g, t_dda *dda, float current_dist);
void	calculate_dda_steps(t_dda *dda, t_player *player);
void	init_dda_values(t_dda *dda, t_player *player, int screen_x);
#endif