#include "exec_reborn.h"

/**
 * @brief Initializes core DDA values
 * @param dda DDA structure to initialize
 * @param player Reference to player position/direction
 * @param screen_x Current screen X position [0-SCREEN_WIDTH]
 * 
 * Calculates ray direction and initial grid position.
 */
static void init_dda_values(t_dda *dda, const t_player *player, int screen_x)
{
    float camera_x = 2 * screen_x / (float)SCREEN_WIDTH - 1;
    dda->ray_dir_x = player->camera.dir_x + player->camera.plane_x * camera_x;
    dda->ray_dir_y = player->camera.dir_y + player->camera.plane_y * camera_x;
    
    dda->map_current_x = (int)player->x;
    dda->map_current_y = (int)player->y;
    
    dda->delta_dist_x = fabsf(1 / dda->ray_dir_x);
    dda->delta_dist_y = fabsf(1 / dda->ray_dir_y);
}

/**
 * @brief Calculates DDA step increments
 * @param dda DDA structure containing directions
 * @param player Player position for initial distance calculation
 * 
 * Determines movement direction through grid (left/right and up/down).
 */
static void calculate_dda_steps(t_dda *dda, const t_player *player)
{
    if (dda->ray_dir_x < 0) {
        dda->step_x = -1;
        dda->side_dist_x = (player->x - dda->map_current_x) * dda->delta_dist_x;
    } else {
        dda->step_x = 1;
        dda->side_dist_x = (dda->map_current_x + 1.0f - player->x) * dda->delta_dist_x;
    }
    
    if (dda->ray_dir_y < 0) {
        dda->step_y = -1;
        dda->side_dist_y = (player->y - dda->map_current_y) * dda->delta_dist_y;
    } else {
        dda->step_y = 1;
        dda->side_dist_y = (dda->map_current_y + 1.0f - player->y) * dda->delta_dist_y;
    }
}

/**
 * @brief Performs one DDA iteration
 * @param dda Structure containing current DDA state
 * 
 * Advances one grid cell according to DDA algorithm.
 */
static void advance_dda(t_dda *dda)
{
    if (dda->side_dist_x < dda->side_dist_y) {
        dda->side_dist_x += dda->delta_dist_x;
        dda->map_current_x += dda->step_x;
        dda->side = 0;
    } else {
        dda->side_dist_y += dda->delta_dist_y;
        dda->map_current_y += dda->step_y;
        dda->side = 1;
    }
}

/**
 * @brief Checks if ray hit wall or reached max distance
 * @param dda Current DDA state
 * @param current_dist Ray's current travel distance
 * @return 1 if wall collision, 0 otherwise
 */
static int check_collision(t_game *g, const t_dda *dda, float current_dist)
{
    if (current_dist > MAX_RENDER_DISTANCE)
        return 0;
    return (g->map.map[dda->map_current_x][dda->map_current_y] > 0);
}