#include "../include/cub.h"

void	mlx_deletion_func (void *mlx_t_adr)
{
	mlx_terminate(mlx_t_adr);
}

void	fd_deletion_func (void *fd_adr)
{
	int	*i;

	i = fd_adr;
	close(*i);
}

void	init_mlx(t_game *game)
{
	mlx_set_setting(MLX_MAXIMIZED, true);
	game->mlx = mlx_init(WIDTH, HEIGHT, "CUB3D", true);
	if (!game->mlx)
		nuclear_exit(ft_error(WHERE, "init() failure", EXIT_FAILURE));
}

draw_screen(t_game *g)
{
	unsigned int	x;
	t_player	*map;
	t_player	*player;
	double	camera[DIM];
	double	ray_dir[DIM];
	int		map_block_position[DIM];
	double	side_dist[DIM];
	double	delta_dist[DIM];
	double perpWallDist;

	player = &g->player;
	map = &g->map;
	while(x < SCREEN_WIDTH)
	{
		camera[X] = 2 * x / SCREEN_WIDTH; //X coord in camera space
		ray_dir[X] = g->player.direction[X] + g->player.plane[X] * camera[X];
		ray_dir[Y] = g->player.direction[X] + g->player.plane[X] * camera[X];


		//which block of the map are we in
		map_block_position[X] = (int) g->player.position[X];
		map_block_position[X] = (int) g->player.position[Y];

		if (ray_dir[X] == 0)
			delta_dist[X] = 1e30;
		else
			delta_dist[X] = abs(1 / ray_dir[X]);
		if (ray_dir[Y] == 0)
			delta_dist[Y] = 1e30;
		else
			delta_dist[Y] = abs(1 / ray_dir[Y]);

		x++;

		//what direction to step in x or y-direction (either +1 or -1)
		double	step[DIM];

		bool hit; //was there a wall hit?
		int side; //was a NS or a EW wall hit?
		//calculate step and initial side_dist
		if(ray_dir[X] < 0)
		{
			step[X] = -1;
			side_dist[X] = (player->position[X] - map_block_position[X]) * delta_dist[X];
		}
		else
		{
			step[X] = 1;
			side_dist[X] = (map_block_position[X] + 1.0 - player->position[X]) * delta_dist[X];
		}
		if(ray_dir[Y] < 0)
		{
			step[Y] = -1;
			side_dist[Y] = (player->position[Y] - map_block_position[Y]) * delta_dist[Y];
		}
		else
		{
			step[Y] = 1;
			side_dist[Y] = (map_block_position[Y] + 1.0 - player->position[Y]) * delta_dist[Y];
		}

		//perform DDA
		hit = false;
		while(hit == false)
		{
			//jump to next map square, either in x-direction, or in y-direction
			if(side_dist[X] < side_dist[Y])
			{
				side_dist[X] += delta_dist[X];
				map_block_position[X] += step[X];
				side = 0;
			}
			else
			{
				side_dist[Y] += delta_dist[Y];
				map_block_position[Y] += step[Y];
				side = 1;
			}
			//Check if ray has hit a wall
			if(g->map.map[map_block_position[X]][map_block_position[Y]] > 0)
				hit = true;
		}
	  //Calculate distance projected on camera direction. This is the shortest distance from the point where the wall is
      //hit to the camera plane. Euclidean to center camera point would give fisheye effect!
      //This can be computed as (map_block_position[X] - posX + (1 - step[X]) / 2) / rayDirX for side == 0, or same formula with Y
      //for size == 1, but can be simplified to the code below thanks to how side_dist and delta_dist are computed:
      //because they were left scaled to |rayDir|. side_dist is the entire length of the ray above after the multiple
      //steps, but we subtract delta_dist once because one step more into the wall was taken above.
      if(side == 0) perpWallDist = (side_dist[X] - delta_dist[X]);
      else          perpWallDist = (side_dist[Y] - delta_dist[Y]);

      //Calculate height of line to draw on screen
      int lineHeight = (int)(SCREEN_HEIGHT / perpWallDist);

      //calculate lowest and highest pixel to fill in current stripe
      int drawStart = -lineHeight / 2 + SCREEN_HEIGHT / 2;
      if(drawStart < 0) drawStart = 0;
      int drawEnd = lineHeight / 2 + SCREEN_HEIGHT / 2;
      if(drawEnd >= SCREEN_HEIGHT) drawEnd = SCREEN_HEIGHT - 1;

      //choose wall color
    //   ColorRGB color;
    //   switch(g->map.map[map_block_position[X]][map_block_position[Y]])
    //   {
    //     case 1:  color = RGB_Red;    break; //red
    //     case 2:  color = RGB_Green;  break; //green
    //     case 3:  color = RGB_Blue;   break; //blue
    //     case 4:  color = RGB_White;  break; //white
    //     default: color = RGB_Yellow; break; //yellow
    //   }

    //   //give x and y sides different brightness
    //   if(side == 1) {color = color / 2;}

    //   //draw the pixels of the stripe as a vertical line
    //   verLine(x, drawStart, drawEnd, color);
	}
	// g->time.old = g->time.now;
	// g->time.now = ;
	// g->time.taken_to_draw_frame = g->time.now - g->time.old;

}

int	main(int argc, char **argv)
{
	t_parsing_map 		*parse;
	t_game				*game;

	// --- INIT

	char *mapdata[] = \
	{
		"        1111111111111111111111111",
		"        1000000000110000000000001",
		"        1011000001110000000000001",
		"        1001000000000000000000001",
		"111111111011000001110000000000001",
		"100000000011000001110111111111111",
		"11110111111111011100000010001    ",
		"11110111111111011101010010001    ",
		"11000000110101011100000010001    ",
		"10000000000000001100000010001    ",
		"10000000000000001101010010001    ",
		"1100000111010101111101111000111  ",
		"11110111 1110101 101111010001    ",
		"11111111 1111111 111111111111    ",
		"                                 ",
		"111                              ",
		"101                              ",
		"111                              ",
		NULL
	};
		
	game->map.map = mapdata;
	game->map.x_max = 33;
	game->map.y_max = 17;

	game->player.direction[X] = 13 * GRID_X;
	game->player.direction[X] = 5 * GRID_Y;

	game->player.position[X] = -1;
	game->player.position[X] = 1;

	// --- INIT END

	if (argc != 2)
		return (ft_error(WHERE, "Bad argument", EXIT_FAILURE));
	
	memory_manager(CREATE, NULL, NULL);
	memory_manager_area_create(ZONE_1, &free, 256);
	memory_manager_area_create(ZONE_FDS, &fd_deletion_func, 10);
	memory_manager_area_create(ZONE_MLX, &mlx_deletion_func, 1);

	game = safe_calloc(ZONE_1, 1, sizeof(t_game));
	parse = safe_calloc(ZONE_1, 1, sizeof(t_parsing_map));

	// if (init(game, argv[1]) != EXIT_SUCCESS)
	//  	nuclear_exit(ft_error(WHERE, "init() failure", EXIT_FAILURE));

	init_mlx(game);
	mlx_loop(game->mlx);

	memory_manager(DESTROY, NULL, NULL);
	printf(BGREEN"\tDone !\n"RESET);
	return (EXIT_SUCCESS);
}
