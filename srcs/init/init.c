/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julcalde <julcalde@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 14:12:07 by hpehliva          #+#    #+#             */
/*   Updated: 2025/07/22 20:23:48 by julcalde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

/*
** Initializes the garbage collector and mlx structure in the game data.
** Sets the mlx pointer and image pointer to NULL.
**
** @param data Pointer to the game structure containing garbage collector and
** mlx data.
*/
static void	init_garbage_and_mlx(t_game *data)
{
	garbco_init(&data->garbco);
	data->mlx = NULL;
	data->img = NULL;
}

/*
** Initializes player data with default values.
** Sets the player's position, direction, plane, and spawn direction.
**
* @param data Pointer to the game structure containing player data.
*/
static void	init_player_data(t_game *data)
{
	data->player.x = 0.0;
	data->player.y = 0.0;
	data->player.dir_x = 0.0;
	data->player.dir_y = -1.0;
	data->player.plane_x = 0.66;
	data->player.plane_y = 0.0;
	data->player.spawn_dir = 0.0;
	data->player_found = 0;
}

/*
* Initializes the map and textures in the game structure.
* Sets default values for the map grid, dimensions, textures, and colors.
*
* @param data Pointer to the game structure to be initialized.
*/
static void	init_map_and_textures(t_game *data)
{
	int	i;

	data->map.grid = NULL;
	data->map.width = 0;
	data->map.height = 0;
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
}

/*
** Initializes the game data structure with default values.
** Sets up the garbage collector, player data, map, and textures.
**
** @param data Pointer to the game structure to be initialized.
*/
void	init_data(t_game *data)
{
	init_garbage_and_mlx(data);
	init_player_data(data);
	init_map_and_textures(data);
}

/*
** Initializes the game structure and sets up the mlx window and image.
** If any initialization fails, it cleans up and exits with an error.
*
** @param game Pointer to the game structure to be initialized.
*/
void	init_game(t_game *game)
{
	init_data(game);
	game->mlx = mlx_init(WIDTH, HEIGHT, WIN_TITLE, true);
	if (!game->mlx)
		mlx_error("mlx_init");
	game->img = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	if (!game->img)
	{
		mlx_terminate(game->mlx);
		mlx_error("mlx_new_image");
	}
	if (mlx_image_to_window(game->mlx, game->img, 0, 0) < 0)
	{
		mlx_delete_image(game->mlx, game->img);
		mlx_terminate(game->mlx);
		mlx_error("mlx_image_to_window");
	}
}
