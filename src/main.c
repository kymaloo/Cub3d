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
	mlx_image_t* img;

	game->mlx = mlx_init(WIDTH, HEIGHT, "CUB3D", true);
	if (!game->mlx)
		nuclear_exit(ft_error(WHERE, "init() failure", EXIT_FAILURE));
	img = mlx_new_image(game->mlx, 1920, 1080);
	mlx_image_to_window(game->mlx, img, 0, 0);
	game->texture->image->img_window = img;
	game->texture->player = mlx_load_png("images/p3_stand1.png");
	game->texture->image->player_img = mlx_texture_to_image(game->mlx, game->texture->player);
	mlx_image_to_window(game->mlx, game->texture->image->player_img, game->player->position[X] * (TILE_SIZE_MINIMAP), game->player->position[Y] * (TILE_SIZE_MINIMAP));

}

int	main(int argc, char **argv)
{
	t_data *data;

	data = NULL;
	if (DEBUG)
	{
		int i = 0;
		while (i++ < 15)
			printf("\n\n\n");
		printf(BBLUE"\n%s:"BBLUE" executing program:"BYELLOW" mode: Debug"RESET"\n\n\n", argv[0]);
		printf(BWHITE"parsing debug infos:"RESET"\n");
	}
	if (argc != 2)
		return (ft_error(WHERE, "Bad argument", EXIT_FAILURE));
	create_memory_manager(&data);
	if (init(data, argv[1]) != EXIT_SUCCESS)
	  	nuclear_exit(ft_error(WHERE, "init() failure", EXIT_FAILURE));
	stock_radian(data->game->player);
	if (DEBUG)
	{
		print_debug_prefix(WHERE_FUNC, "");
		print_player_infos(data->game->player, "");
		printf(BWHITE"game hooks debug infos:"RESET"\n");
	}
	init_mlx(data->game);
	init_textures(data->game);
	if (mlx_loop_hook(data->game->mlx, &ft_loop_hook, data->game))
	{
		data->game->toggles.catch_mouse_cursor = true;
		mlx_set_cursor_mode(data->game->mlx, MLX_MOUSE_DISABLED);
		data->game->toggles.minimap = false;
		mlx_cursor_hook(data->game->mlx, &ft_cursor_hook, data->game);
		mlx_mouse_hook(data->game->mlx, &ft_mouse_hook, data->game);
		mlx_key_hook(data->game->mlx, &ft_keys_hook, data->game);
		mlx_loop(data->game->mlx);
	}
	mlx_terminate(data->game->mlx);
	memory_manager(DESTROY, NULL, NULL);
	if (DEBUG)
		printf(BBLUE"\n\n%s:"BBLUE" executing program:"BGREEN" Done !\n"RESET, argv[0]);
	return (EXIT_SUCCESS);
}

void	print_minimap(t_game *g)
{
	
	if (mlx_is_key_down(g->mlx, MLX_KEY_M))
	{
		draw_map(g);
		g->texture->image->player_img->enabled = true;
		g->texture->image->img_window->enabled = true;
	}
	else if (mlx_is_key_down(g->mlx, MLX_KEY_N))
	{
		g->texture->image->player_img->enabled = false;
		g->texture->image->img_window->enabled = false;
	}
}

void	create_memory_manager(t_data **data)
{
	memory_manager(CREATE, NULL, NULL);
	memory_manager_area_create(ZONE_PARSE, &free, 256);
	memory_manager_area_create(ZONE_FDS, &fd_deletion_func, 10);
	memory_manager_area_create(ZONE_MLX, &mlx_deletion_func, 1);
	*data = safe_calloc(ZONE_PARSE, 1, sizeof(t_data));
	(*data)->parse = safe_calloc(ZONE_PARSE, 1, sizeof(t_parsing_map));
	(*data)->game = safe_calloc(ZONE_PARSE, 1, sizeof(t_game));
	(*data)->game->texture = safe_calloc(ZONE_PARSE, 1, sizeof(t_texture));
	(*data)->game->texture->image = safe_calloc(ZONE_PARSE, 1, sizeof(t_image));
	(*data)->game->player = safe_calloc(ZONE_PARSE, 1, sizeof(t_player));
	//(*data)->path = safe_calloc(ZONE_PARSE, 1, sizeof(t_path));
	(*data)->game->path = safe_calloc(ZONE_PARSE, 1, sizeof(t_path));
	(*data)->colors = safe_calloc(ZONE_PARSE, 1, sizeof(t_colors));
	(*data)->game->ray = safe_calloc(ZONE_PARSE, 1, sizeof(t_ray));
}

// void	stock_radian(t_player *player)
// {
// 	if (player->facing == 'N')
// 		player->radian = (3 * M_PI / 2);
// 	if (player->facing == 'S')
// 		player->radian = (M_PI / 2);
// 	if (player->facing == 'E')
// 		player->radian = (0);
// 	if (player->facing == 'W')
// 		player->radian = (M_PI);
// }

void stock_radian(t_player *player)
{
	if (player->facing == 'N')
		player->radian = (M_PI / 2);
	else if (player->facing == 'S')
		player->radian = (-M_PI / 2);
	else if (player->facing == 'E')
		player->radian = (2 * M_PI);
	else if (player->facing == 'W')
		player->radian = (M_PI);
	else
		nuclear_exit(ft_error(WHERE, "Bad player direction", EXIT_FAILURE));



//TODO pas certain si c'est un fix de direction ou pas, pas rapport a ma branche (dessus), mais sans doute, oui 
    if (player->facing == 'N')
    {
        player->radian = (3 * M_PI / 2);
        player->position[X] = player->position[X] + 0.5; // Centrer dans la case
        player->position[Y] = player->position[Y] + 0.5;
    }
    else if (player->facing == 'S')
    {
        player->radian = (M_PI / 2);
        player->position[X] = player->position[X] + 0.5;
        player->position[Y] = player->position[Y] + 0.5;
    }
    else if (player->facing == 'E')
    {
        player->radian = 0;
        player->position[X] = player->position[X] + 0.5;
        player->position[Y] = player->position[Y] + 0.5;
    }
    else if (player->facing == 'W')
    {
        player->radian = M_PI;
        player->position[X] = player->position[X] + 0.5;
        player->position[Y] = player->position[Y] + 0.5;
    }
	else
		nuclear_exit(ft_error(WHERE, "Bad player direction", EXIT_FAILURE));

	//ça, je rajoute :
	update_player_direction(player);
}
