/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_key_mov.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julcalde <julcalde@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 13:44:56 by julcalde          #+#    #+#             */
/*   Updated: 2025/07/25 16:11:45 by julcalde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

/*
** move_front - Moves the player to the front based on the plane vector.
** This function calculates the new position by subtracting the plane vector
** multiplied by the move speed from the current position. It checks if the
** new position is valid (not a wall or empty space) before updating the
**  player's position.
**
** @param game Pointer to the game structure containing player and map data.
*/
static void	move_front(t_game *game)
{
	double	new_x;
	double	new_y;

	new_x = game->player.x + game->player.dir_x * MOVE_SPEED;
	new_y = game->player.y + game->player.dir_y * MOVE_SPEED;
	if ((game->map.grid[(int)new_y][(int)new_x] != '1')
		&& (game->map.grid[(int)new_y][(int)new_x] != ' '))
	{
		game->player.x = new_x;
		game->player.y = new_y;
	}
}

/*
** move_back - Moves the player to the back based on the plane vector.
** This function calculates the new position by subtracting the plane vector
** multiplied by the move speed from the current position. It checks if the
** new position is valid (not a wall or empty space) before updating the
**  player's position.
**
** @param game Pointer to the game structure containing player and map data.
*/
static void	move_back(t_game *game)
{
	double	new_x;
	double	new_y;

	new_x = game->player.x - game->player.dir_x * MOVE_SPEED;
	new_y = game->player.y - game->player.dir_y * MOVE_SPEED;
	if ((game->map.grid[(int)new_y][(int)new_x] != '1')
		&& (game->map.grid[(int)new_y][(int)new_x] != ' '))
	{
		game->player.x = new_x;
		game->player.y = new_y;
	}
}

/*
** move_left - Moves the player to the left based on the plane vector.
** This function calculates the new position by subtracting the plane vector
** multiplied by the move speed from the current position. It checks if the
** new position is valid (not a wall or empty space) before updating the
**  player's position.
**
** @param game Pointer to the game structure containing player and map data.
*/
static void	move_left(t_game *game)
{
	double	new_x;
	double	new_y;

	new_x = game->player.x - game->player.plane_x * MOVE_SPEED;
	new_y = game->player.y - game->player.plane_y * MOVE_SPEED;
	if ((game->map.grid[(int)new_y][(int)new_x] != '1')
		&& (game->map.grid[(int)new_y][(int)new_x] != ' '))
	{
		game->player.x = new_x;
		game->player.y = new_y;
	}
}

/*
** move_right - Moves the player to the right based on the plane vector.
** This function calculates the new position by adding the plane vector
** multiplied by the move speed to the current position. It checks if the
** new position is valid (not a wall or empty space) before updating the
**  player's position.
**
** @param game Pointer to the game structure containing player and map data.
*/
static void	move_right(t_game *game)
{
	double	new_x;
	double	new_y;

	new_x = game->player.x + game->player.plane_x * MOVE_SPEED;
	new_y = game->player.y + game->player.plane_y * MOVE_SPEED;
	if ((game->map.grid[(int)new_y][(int)new_x] != '1')
		&& (game->map.grid[(int)new_y][(int)new_x] != ' '))
	{
		game->player.x = new_x;
		game->player.y = new_y;
	}
}

/*
** move_player - Handles player movement based on key inputs.
** This function checks for key presses and updates the player's position
** accordingly. It allows the player to move forward, backward, left, or right
** in the game world.
**
** @param game Pointer to the game structure containing player and map data.
*/
void	move_player(t_game *game)
{
	if (mlx_is_key_down(game->mlx, W))
	{
		move_front(game);
	}
	if (mlx_is_key_down(game->mlx, S))
	{
		move_back(game);
	}
	if (mlx_is_key_down(game->mlx, A))
	{
		move_left(game);
	}
	if (mlx_is_key_down(game->mlx, D))
	{
		move_right(game);
	}
}
