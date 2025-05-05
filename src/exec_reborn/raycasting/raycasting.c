#include "exec_reborn.h"

/**
 * @brief Performs raycasting for single screen column
 * @param player Player data (position/direction)
 * @param screen_x Current screen X position
 * @return Collision information structure
 */
static t_collision_infos cast_single_ray(t_game *g, t_player *player, int screen_x)
{
	t_dda dda;
	t_collision_infos col = {0};
	
	init_dda_values(&dda, player, screen_x);
	calculate_dda_steps(&dda, player);
	
	while (42) {
		advance_dda(&dda);
		float current_dist = calculate_wall_distance(&dda, player);
		
		if (check_collision(g, &dda, current_dist)) {
			col.wall_distance = current_dist;
			determine_wall_face(&col, &dda);
			calculate_wall_hit_position(&col, &dda, player);
			break;
		} else if (current_dist > MAX_RENDER_DISTANCE) {
			col.face = NO_COLLISION;
			break;
		}
	}
	return col;
}

/**
 * @brief Performs complete raycasting pass
 * @param player Player data
 * @param collisions Array to store results
 * 
 * Processes each screen column and populates collision data.
 */
void raycast(t_game *g, t_player *player, t_collision_infos *collisions)
{
	int screen_x = 0;
	while (screen_x < SCREEN_WIDTH) {
		collisions[screen_x] = cast_single_ray(g, player, screen_x);
		screen_x++;
	}
}