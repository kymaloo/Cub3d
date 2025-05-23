#include "../include/cub.h"

bool	is_within_map_boundaries(t_map *map, int x, int y)
{
	if (DEBUG)
	{
		if(x >= map->x_max)
			printf(BRED"\tx:%d >= %d "RESET, x, map->x_max);
		if(x < 0)
			printf(BRED"\tx:%d < 0 "RESET, x);
		if(y >= map->y_max )
			printf(BRED"\ty:%d >= %d "RESET, y, map->y_max);
		if(y < 0 )
			printf(BRED"\ty:%d < 0 "RESET, y);
	}
	if (y >= map->y_max || y < 0 || x >= map->x_max || x < 0)
		return (false);
	return 	(true);
}

void	perform_dda(t_ray *ray, t_map *map)
{
	int tmp = 0;
	
	while (ray->hit == 0)
	{
		if (ray->side_dist_x < ray->side_dist_y)
		{
			ray->side_dist_x += ray->delta_dist_x;
			ray->map_x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->side_dist_y += ray->delta_dist_y;
			ray->map_y += ray->step_y;
			ray->side = 1;
		}
	//	printf("%d ----------- %d\n", ray->map_x, ray->map_y);
		# define DEBUG_DDA false
		if (DEBUG_DDA)
		{
			printf("\nmap max:\t("RED"%3d"RESET","GREEN" %3d"RESET")\n", map->x_max -1, map->y_max - 1);
			printf("n*%d:\t", tmp);
			printf("%15s", "within?:  ");
			is_within_map_boundaries(map, ray->map_x, ray->map_y)? printf(GREEN" Y "RESET): printf(RED" N "RESET);
			printf("("RED"%3d"RESET","GREEN"%3d"RESET")\n", ray->map_x, ray->map_y);

			printf("n*%d:\t", tmp);
			printf("%15s", "wall?:  ");
			(map->grid[ray->map_y][ray->map_x] == '1')? printf(GREEN" Y "RESET): printf(RED" N "RESET);
			printf("("RED"%3d"RESET","GREEN"%3d"RESET")\n", ray->map_x, ray->map_y);

			printf("\n");
			tmp++;
			if (tmp > 100)
				nuclear_exit(EXIT_FAILURE);
		}

		//TODO si hors de la grille : te mettre a l'extremum grille
		if(ray->map_x >= map->x_max)
		{
			ray->map_x = map->x_max - 1;
			ray->hit = 1;
		}
		else if(ray->map_x < 0)
		{
			ray->map_x = 0;
			ray->hit = 1;
		}
		if(ray->map_y >= map->y_max )
		{
			ray->map_y = map->y_max - 1;
			ray->hit = 1;
		}
		else if(ray->map_y < 0 )
		{
			ray->map_y = 0;
			ray->hit = 1;
		}
			


		if (map->grid[ray->map_y][ray->map_x] == '1') // fixes this SEGV
			ray->hit = 1;
	}
}

static void ceilling(t_game *game, int x)
{
	int	y;
	int color_floor;

	y = 0;
	color_floor = C_FLOOR_BROWN;
	while (y < game->ray->draw_start - 2) //FIXME the -2 was necessary, as game->ray->draw_start was set to 1082
	{
		mlx_put_pixel(game->texture->image->img_window, x, y, color_floor);
		y++;
	}
}

static void wall(t_game *game, int x)
{
	int	y;
	int color_floor;

	y = game->ray->draw_start;
	color_floor = (game->ray->side == 1) ? C_BLUE : C_RED;
	while (y <= game->ray->draw_end)
	{
		mlx_put_pixel(game->texture->image->img_window, x, y, color_floor);
		y++;
	}
}

static void floors(t_game *game, int x)
{
	int	y;
	int color_floor;

	y = game->ray->draw_end + 1;
	color_floor = C_GREY_INVALID;
	while (y < HEIGHT)
	{
		mlx_put_pixel(game->texture->image->img_window, x, y, color_floor);
		y++;
	}
}

static	void	setup_colors(t_game *game, int x)
{
	ceilling(game, x);
	wall(game, x);
	floors(game, x);
}

static void	onscreen_line(t_ray *ray, int line_height)
{
	ray->draw_start = -line_height / 2 + HEIGHT / 2;
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	ray->draw_end = line_height / 2 + HEIGHT / 2;
	if (ray->draw_end >= HEIGHT)
		ray->draw_end = HEIGHT - 1;
}

// Voici la version corrigée de votre fonction init_ray
static void init_ray(t_ray *ray, t_player *player, double ray_angle)
{
    ray->dir_x = cos(ray_angle);
    ray->dir_y = sin(ray_angle);
    ray->map_x = (int)player->position[0];
    ray->map_y = (int)player->position[1];
    ray->delta_dist_x = fabs(1 / ray->dir_x);
    ray->delta_dist_y = fabs(1 / ray->dir_y);
    ray->hit = 0;
    if (ray->dir_x < 0)
    {
        ray->step_x = -1;
        ray->side_dist_x = (player->position[0] - ray->map_x) * ray->delta_dist_x;
    }
    else
    {
        ray->step_x = 1;
        ray->side_dist_x = (ray->map_x + 1.0 - player->position[0]) * ray->delta_dist_x;
    }
    if (ray->dir_y < 0)
    {
        ray->step_y = -1;
        ray->side_dist_y = (player->position[1] - ray->map_y) * ray->delta_dist_y;
    }
    else
    {
        ray->step_y = 1;
        ray->side_dist_y = (ray->map_y + 1.0 - player->position[1]) * ray->delta_dist_y;
    }
}

// Voici la version corrigée de votre fonction fish_eyes
static double calculate_perp_wall_dist(t_game *game, double ray_angle)
{
    double perp_wall_dist;
    
    if (game->ray->side == 0)
        perp_wall_dist = (game->ray->map_x - game->player->position[0] + 
                        (1 - game->ray->step_x) / 2) / game->ray->dir_x;
    else
        perp_wall_dist = (game->ray->map_y - game->player->position[1] + 
                        (1 - game->ray->step_y) / 2) / game->ray->dir_y;
    
    // La correction fish-eye est appliquée ici:
    // Multiplier par cos(player_angle - ray_angle)
    double angle_diff = game->player->radian - ray_angle;
    // Normaliser l'angle
    while (angle_diff > M_PI)
        angle_diff -= 2 * M_PI;
    while (angle_diff < -M_PI)
        angle_diff += 2 * M_PI;
    
    // Appliquer la correction fish-eye
    perp_wall_dist *= cos(angle_diff);
    
    return perp_wall_dist;
}

// Voici la version corrigée de votre fonction raycast
void raycast(t_game *game)
{
    int x;
    int line_height;
    double camera_x;
    double ray_angle;
    double perp_wall_dist;
    
    x = 0;
    while (x < WIDTH)
    {
        // Calculer la position x sur le plan de la caméra
        camera_x = 2 * x / (double)WIDTH - 1;
        
        // Calculer la direction du rayon correctement
        // Pour un FOV de 66 degrés (standard pour Wolfenstein 3D), on peut utiliser:
        // La direction du joueur + la direction ajustée par camera_x
        ray_angle = game->player->radian + atan2(camera_x, 1.0);
        
        // Alternative plus simple si vous préférez:
        // ray_angle = game->player->radian + camera_x * (FOV / 2) * M_PI / 180.0;
        // où FOV est votre champ de vision en degrés (ex: 66.0)
        
        init_ray(game->ray, game->player, ray_angle);
        perform_dda(game->ray, game->map);
        
        // Utiliser la fonction améliorée pour calculer la distance perpendiculaire
        perp_wall_dist = calculate_perp_wall_dist(game, ray_angle);
        
		if (perp_wall_dist == 0)
		{
			perp_wall_dist = 1; //TODO may need to be tweaked later
		}
		line_height = (int)(HEIGHT / perp_wall_dist);
        onscreen_line(game->ray, line_height);
        setup_colors(game, x);
        x++;
    }
}
