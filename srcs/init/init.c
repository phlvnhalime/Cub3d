/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpehliva <hpehliva@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 14:12:07 by hpehliva          #+#    #+#             */
/*   Updated: 2025/07/12 14:12:08 by hpehliva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	init_data(t_game *data)
{
	// First i can start with the function garbage
	garbco_init(&data->garbco);
	/*
		initialized img and mlx to NULL
	*/
	data->mlx = NULL;
	data->img = NULL;
	// Initialize player position
	data->player.x = 0.0;
	data->player.y = 0.0;
	data->player.dir_x = 0.0;
	data->player.dir_y = -1.0;   // Facing down the Y-axis
	data->player.plane_x = 0.66; // Camera plane X component
	data->player.plane_y = 0.0;
	data->player.spawn_dir = 0.0;
	// Initialize map
	data->map.grid = NULL;
	data->map.width = 0;
	data->map.height = 0;
	// initialize textures
	for (int i = 0; i < 4; i++)
	{
		data->textures[i].texture = NULL;
		data->textures[i].path = NULL;
	}
	// Initialize colors
	data->floor_color.r = 0;
	data->floor_color.g = 0;
	data->floor_color.b = 0;
	data->ceiling_color.r = 0;
	data->ceiling_color.g = 0;
	data->ceiling_color.b = 0;
	// Initialized texture
	data->texture_count = 0;
	data->color_count = 0;
	data->map_started = 0; // Flag to indicate if the map has started
	data->map_ended = 0;   // Flag to indicate if the map has ended
	data->map_valid = 0;   // Flag to indicate if the map is valid
	data->player_found = 0; // Flag to indicate
}

void	init_game(t_game *game)
{
	init_data(game);
	// Initialize MLX42
	game->mlx = mlx_init(WIDTH, HEIGHT, WIN_TITLE, true);
	if (!game->mlx)
	{
		ft_putstr_fd("Error: MLX42 initialization failed\n", 2);
		garbco_game(game);
		exit(EXIT_FAILURE);
	}
	// Initialize the game image
	game->img = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	if (!game->img)
	{
		ft_putstr_fd("Error: Image initialization failed\n", 2);
		garbco_game(game);
		exit(EXIT_FAILURE);
	}
	if(mlx_image_to_window(game->mlx, game->img, 0, 0) < 0)
	{
		ft_putstr_fd("Error: Failed to display image in window\n", 2);
		garbco_game(game);
		exit(EXIT_FAILURE);
	}
	DEBUG_PRINT(GRN"Game initialized successfully\n"RST);
}
