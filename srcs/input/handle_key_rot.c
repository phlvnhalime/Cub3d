/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_key_rot.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julcalde <julcalde@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 13:45:36 by julcalde          #+#    #+#             */
/*   Updated: 2025/07/22 20:27:54 by julcalde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

/*
** rotate_player_left - Rotates the player to the left.
** This function calculates the new direction and plane vectors by applying
** a rotation transformation using the defined ROT_SPEED. It updates the
** player's direction and plane vectors accordingly.
**
** @param game Pointer to the game structure containing player data.
*/
static void	rotate_player_left(t_game *game)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = game->player.dir_x;
	game->player.dir_x = game->player.dir_x * cos(-ROT_SPEED)
		- game->player.dir_y * sin(-ROT_SPEED);
	game->player.dir_y = old_dir_x * sin(-ROT_SPEED) + game->player.dir_y
		* cos(-ROT_SPEED);
	old_plane_x = game->player.plane_x;
	game->player.plane_x = game->player.plane_x * cos(-ROT_SPEED)
		- game->player.plane_y * sin(-ROT_SPEED);
	game->player.plane_y = old_plane_x * sin(-ROT_SPEED) + game->player.plane_y
		* cos(-ROT_SPEED);
}

/*
** rotate_player_right - Rotates the player to the right.
** This function calculates the new direction and plane vectors by applying
** a rotation transformation using the defined ROT_SPEED. It updates the
** player's direction and plane vectors accordingly.
**
** @param game Pointer to the game structure containing player data.
*/
static void	rotate_player_right(t_game *game)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = game->player.dir_x;
	game->player.dir_x = game->player.dir_x * cos(ROT_SPEED)
		- game->player.dir_y * sin(ROT_SPEED);
	game->player.dir_y = old_dir_x * sin(ROT_SPEED) + game->player.dir_y
		* cos(ROT_SPEED);
	old_plane_x = game->player.plane_x;
	game->player.plane_x = game->player.plane_x * cos(ROT_SPEED)
		- game->player.plane_y * sin(ROT_SPEED);
	game->player.plane_y = old_plane_x * sin(ROT_SPEED) + game->player.plane_y
		* cos(ROT_SPEED);
}

/*
** rotate_player - Handles player rotation based on key inputs.
** This function checks for key presses and rotates the player left or right
** accordingly. It updates the player's direction and plane vectors based on
** the rotation speed defined in ROT_SPEED.
**
** @param game Pointer to the game structure containing player data.
*/
void	rotate_player(t_game *game)
{
	if (mlx_is_key_down(game->mlx, LEFT))
	{
		rotate_player_left(game);
	}
	if (mlx_is_key_down(game->mlx, RIGHT))
	{
		rotate_player_right(game);
	}
}
