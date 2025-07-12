/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julcalde <julcalde@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 00:26:50 by julcalde          #+#    #+#             */
/*   Updated: 2025/07/12 13:46:02 by julcalde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static void	init_colors_and_textures(t_game *data)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		data->textures[i].texture = NULL;
		data->textures[i].path = NULL;
		i++;
	}
	data->floor_color.r = 0;
	data->floor_color.g = 0;
	data->floor_color.b = 0;
	data->ceiling_color.r = 0;
	data->ceiling_color.g = 0;
	data->ceiling_color.b = 0;
	data->texture_count = 0;
	data->color_count = 0;
	data->map_started = 0;
	data->map_ended = 0;
	data->map_valid = 0;
	data->player_found = 0;
}

/*
	This function initializes the garbage collector to manage memory cleanup.
	It also initializes the game data structure with default values, 
	it sets up the player position, direction, and camera plane,
	as well as initializing the map and textures.
*/
void	init_data(t_game *data)
{
	garbco_init(&data->garbco);
	data->mlx = NULL;
	data->img = NULL;
	data->player.x = 0.0;
	data->player.y = 0.0;
	data->player.dir_x = 0.0;
	data->player.dir_y = -1.0;
	data->player.plane_x = 0.66;
	data->player.plane_y = 0.0;
	data->player.spawn_dir = 0.0;
	data->map.grid = NULL;
	data->map.width = 0;
	data->map.height = 0;
	init_colors_and_textures(data);
}

/*
	This function initializes the game data, creates a new MLX instance,
	and creates a new image to be displayed in the window.
	It also checks for errors during initialization and exits the program
	if any errors occur.
*/
void	init_game(t_game *game)
{
	init_data(game);
	game->mlx = mlx_init(WIDTH, HEIGHT, WIN_TITLE, true);
	if (!game->mlx)
	{
		ft_putstr_fd("Error: MLX42 initialization failed\n", 2);
		garbco_game(game);
		exit(EXIT_FAILURE);
	}
	game->img = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	if (!game->img)
	{
		ft_putstr_fd("Error: Image initialization failed\n", 2);
		garbco_game(game);
		exit(EXIT_FAILURE);
	}
	if (mlx_image_to_window(game->mlx, game->img, 0, 0) < 0)
	{
		ft_putstr_fd("Error: Failed to display image in window\n", 2);
		garbco_game(game);
		exit(EXIT_FAILURE);
	}
	DEBUG_PRINT(GRN"Game initialized successfully\n"RST);
}
