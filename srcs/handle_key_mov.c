/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_key_mov.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julcalde <julcalde@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 13:20:34 by julcalde          #+#    #+#             */
/*   Updated: 2025/07/12 15:57:52 by julcalde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"
#include "../include/mlx.h"

/*
	* This function moves the player forward in the direction they are facing.
	* It calculates the new position based on the player's direction vector and
	* checks if the new position is valid (not a wall) before updating the 
	* player's position.
	* @param game: Pointer to the game structure containing the player and map.
	* If the new position is valid, it updates the player's x and y coordinates.
	* If the new position is a wall ('1'), it does not update the player's position.
*/
void	move_player_front(t_game *game)
{
	double	new_x;
	double	new_y;

	new_x = game->player.x + game->player.dir_x * MOVE_SPEED;
		new_y = game->player.y + game->player.dir_y * MOVE_SPEED;
	if (game->map.grid[(int)new_y][(int)new_x] != '1')
	{
		game->player.x = new_x;
		game->player.y = new_y;
	}
}

/*
	* This function moves the player backward in the direction they are facing.
	* It calculates the new position based on the player's direction vector and
	* checks if the new position is valid (not a wall) before updating the 
	* player's position.
	* @param game: Pointer to the game structure containing the player and map.
	* If the new position is valid, it updates the player's x and y coordinates.
	* If the new position is a wall ('1'), it does not update the player's position.
*/
void	move_player_back(t_game *game)
{
	double	new_x;
	double	new_y;

	new_x = game->player.x - game->player.dir_x * MOVE_SPEED;
	new_y = game->player.y - game->player.dir_y * MOVE_SPEED;
	if (game->map.grid[(int)new_y][(int)new_x] != '1')
	{
		game->player.x = new_x;
		game->player.y = new_y;
	}
}

/*
	* This function moves the player leftward in the direction they are facing.
	* It calculates the new position based on the player's direction vector and
	* checks if the new position is valid (not a wall) before updating the 
	* player's position.
	* @param game: Pointer to the game structure containing the player and map.
	* If the new position is valid, it updates the player's x and y coordinates.
	* If the new position is a wall ('1'), it does not update the player's position.
*/
void	move_player_left(t_game *game)
{
	double	new_x;
	double	new_y;

	new_x = game->player.x - game->player.plane_x * MOVE_SPEED;
	new_y = game->player.y - game->player.plane_y * MOVE_SPEED;
	if (game->map.grid[(int)new_y][(int)new_x] != '1')
	{
		game->player.x = new_x;
		game->player.y = new_y;
	}
}

/*
	* This function moves the player rightward in the direction they are facing.
	* It calculates the new position based on the player's direction vector and
	* checks if the new position is valid (not a wall) before updating the 
	* player's position.
	* @param game: Pointer to the game structure containing the player and map.
	* If the new position is valid, it updates the player's x and y coordinates.
	* If the new position is a wall ('1'), it does not update the player's position.
*/
void	move_player_right(t_game *game)
{
	double	new_x;
	double	new_y;

	new_x = game->player.x + game->player.plane_x * MOVE_SPEED;
	new_y = game->player.y + game->player.plane_y * MOVE_SPEED;
	if (game->map.grid[(int)new_y][(int)new_x] != '1')
	{
		game->player.x = new_x;
		game->player.y = new_y;
	}
}

/*
	* This function handles the player's movement based on key presses.
	* It checks if the W, S, A, or D keys are pressed and calls the corresponding
	* movement function to update the player's position.
	* @param game: Pointer to the game structure containing the player and map.
	
	- If the W key is pressed, it moves the player forward.
	
	- If the S key is pressed, it moves the player backward.
	
	- If the A key is pressed, it moves the player leftward.
	
	- If the D key is pressed, it moves the player rightward.
*/
void	move_player(t_game *game)
{
	if (mlx_is_key_down(game->mlx, W))
	{
		move_player_front(game);
	}
	if (mlx_is_key_down(game->mlx, S))
	{
		move_player_back(game);
	}
	if (mlx_is_key_down(game->mlx, A))
	{
		move_player_left(game);
	}
	if (mlx_is_key_down(game->mlx, D))
	{
		move_player_right(game);
	}
}
