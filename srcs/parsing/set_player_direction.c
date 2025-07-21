/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_player_direction.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julcalde <julcalde@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 11:55:39 by julcalde          #+#    #+#             */
/*   Updated: 2025/07/21 13:37:07 by julcalde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

// ORIGINAL VERSION of set_player_direction.c

// void	set_player_direction(t_game *game, char spawn_char)
// {
// 	game->player.spawn_char = spawn_char;
// 	if (spawn_char == 'N')
// 	{
// 		game->player.dir_x = 0.0;
// 		game->player.dir_y = -1.0;
// 		game->player.plane_x = 0.66;
// 		game->player.plane_y = 0.0;
// 		game->player.spawn_dir = 90.0;
// 	}
// 	else if (spawn_char == 'S')
// 	{
// 		game->player.dir_x = 0.0;
// 		game->player.dir_y = 1.0;
// 		game->player.plane_x = -0.66;
// 		game->player.plane_y = 0.0;
// 		game->player.spawn_dir = 270.0;
// 	}
// 	else if (spawn_char == 'E')
// 	{
// 		game->player.dir_x = 1.0;
// 		game->player.dir_y = 0.0;
// 		game->player.plane_x = 0.0;
// 		game->player.plane_y = 0.66;
// 		game->player.spawn_dir = 0.0;
// 	}
// 	else if (spawn_char == 'W')
// 	{
// 		game->player.dir_x = -1.0;
// 		game->player.dir_y = 0.0;
// 		game->player.plane_x = 0.0;
// 		game->player.plane_y = -0.66;
// 		game->player.spawn_dir = 180.0;
// 	}
// 	DEBUG_PRINT(GRN "Player direction set to '%c' : dir(%.2f, %.2f) 
//  plane(%.2f, %.2f) spawn_dir(%.2f)\n" RST, spawn_char, game->player.dir_x, 
//  game->player.dir_y, game->player.plane_x, game->player.plane_y, 
//  game->player.spawn_dir);
// }

static void	set_north_direction(t_game *game)
{
	game->player.dir_x = 0.0;
	game->player.dir_y = -1.0;
	game->player.plane_x = 0.66;
	game->player.plane_y = 0.0;
	game->player.spawn_dir = 90.0;
}

static void	set_south_direction(t_game *game)
{
	game->player.dir_x = 0.0;
	game->player.dir_y = 1.0;
	game->player.plane_x = -0.66;
	game->player.plane_y = 0.0;
	game->player.spawn_dir = 270.0;
}

static void	set_east_direction(t_game *game)
{
	game->player.dir_x = 1.0;
	game->player.dir_y = 0.0;
	game->player.plane_x = 0.0;
	game->player.plane_y = 0.66;
	game->player.spawn_dir = 0.0;
}

static void	set_west_direction(t_game *game)
{
	game->player.dir_x = -1.0;
	game->player.dir_y = 0.0;
	game->player.plane_x = 0.0;
	game->player.plane_y = -0.66;
	game->player.spawn_dir = 180.0;
}

void	set_player_direction(t_game *game, char spawn_char)
{
	game->player.spawn_char = spawn_char;
	if (spawn_char == 'N')
		set_north_direction(game);
	else if (spawn_char == 'S')
		set_south_direction(game);
	else if (spawn_char == 'E')
		set_east_direction(game);
	else if (spawn_char == 'W')
		set_west_direction(game);
	DEBUG_PRINT(GRN "Player direction set to '%c' : \
		dir(%.2f, %.2f) plane(%.2f, %.2f) spawn_dir(%.2f)\n" \
		RST, spawn_char, game->player.dir_x, game->player.dir_y, \
		game->player.plane_x, game->player.plane_y, game->player.spawn_dir);
}
