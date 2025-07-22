/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_player_direct.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julcalde <julcalde@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 13:38:02 by hpehliva          #+#    #+#             */
/*   Updated: 2025/07/22 23:03:59 by julcalde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

/*
** set_north_direction - Sets the player's direction to north.
** It updates the player's direction vector and plane vector
** to face north, with the direction vector pointing up
** and the plane vector pointing right.
**
** @param game: Pointer to the game structure containing the player.
*/
static void	set_north_direction(t_game *game)
{
	game->player.dir_x = 0.0;
	game->player.dir_y = -1.0;
	game->player.plane_x = 0.66;
	game->player.plane_y = 0.0;
	game->player.spawn_dir = 90.0;
}

/*
** set_south_direction - Sets the player's direction to south.
** It updates the player's direction vector and plane vector
** to face south, with the direction vector pointing down
** and the plane vector pointing left.
**
** @param game: Pointer to the game structure containing the player.
*/
static void	set_south_direction(t_game *game)
{
	game->player.dir_x = 0.0;
	game->player.dir_y = 1.0;
	game->player.plane_x = -0.66;
	game->player.plane_y = 0.0;
	game->player.spawn_dir = 270.0;
}

/*
** set_east_direction - Sets the player's direction to east.
** It updates the player's direction vector and plane vector
** to face east, with the direction vector pointing right
** and the plane vector pointing up.
**
** @param game: Pointer to the game structure containing the player.
*/
static void	set_east_direction(t_game *game)
{
	game->player.dir_x = 1.0;
	game->player.dir_y = 0.0;
	game->player.plane_x = 0.0;
	game->player.plane_y = 0.66;
	game->player.spawn_dir = 0.0;
}

/*
** set_west_direction - Sets the player's direction to west.
** It updates the player's direction vector and plane vector
** to face west, with the direction vector pointing left
** and the plane vector pointing down.
**
** @param game: Pointer to the game structure containing the player.
*/
static void	set_west_direction(t_game *game)
{
	game->player.dir_x = -1.0;
	game->player.dir_y = 0.0;
	game->player.plane_x = 0.0;
	game->player.plane_y = -0.66;
	game->player.spawn_dir = 180.0;
}

/*
** set_player_direction - Sets the player's direction based on the 
** spawn character.
** It updates the player's direction vector and plane vector
** according to the specified spawn character ('N', 'S', 'E', 'W').
** It also sets the spawn character in the player structure.
**
** @param game: Pointer to the game structure containing the player.
** @param spawn_char: The character indicating the player's spawn direction.
*/
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
}
