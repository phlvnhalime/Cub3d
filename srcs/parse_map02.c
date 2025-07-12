/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map02.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julcalde <julcalde@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 19:25:52 by julcalde          #+#    #+#             */
/*   Updated: 2025/07/12 20:00:05 by julcalde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static void	set_player_north(t_game *game)
{
	game->player.dir_x = 0.0;
	game->player.dir_y = -1.0;
	game->player.plane_x = 0.66;
	game->player.plane_y = 0.0;
	game->player.spawn_dir = 90.0;
}

static void	set_player_south(t_game *game)
{
	game->player.dir_x = 0.0;
	game->player.dir_y = 1.0;
	game->player.plane_x = -0.66;
	game->player.plane_y = 0.0;
	game->player.spawn_dir = 270.0;
}

static void	set_player_east(t_game *game)
{
	game->player.dir_x = 1.0;
	game->player.dir_y = 0.0;
	game->player.plane_x = 0.0;
	game->player.plane_y = 0.66;
	game->player.spawn_dir = 0.0;
}

static void	set_player_west(t_game *game)
{
	game->player.dir_x = -1.0;
	game->player.dir_y = 0.0;
	game->player.plane_x = 0.0;
	game->player.plane_y = -0.66;
	game->player.spawn_dir = 180.0;
}

/*
	Sets the player's direction based on the spawn character.
	- 'N' for North
	- 'S' for South
	- 'E' for East
	- 'W' for West
*/
void	set_player_direction(t_game *game, char spawn_char)
{
	game->player.spawn_char = spawn_char;
	if (spawn_char == 'N')
	{
		set_player_north(game);
	}
	else if (spawn_char == 'S')
	{
		set_player_south(game);
	}
	else if (spawn_char == 'E')
	{
		set_player_east(game);
	}
	else if (spawn_char == 'W')
	{
		set_player_west(game);
	}
	DEBUG_PRINT(GRN"Player direction set to '%c' : dir(%.2f, %.2f) \
		plane(%.2f, %.2f) spawn_dir(%.2f)\n"RST, spawn_char, game->player.dir_x, \
		game->player.dir_y, game->player.plane_x, game->player.plane_y, \
		game->player.spawn_dir);
}
