/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_key_rot.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julcalde <julcalde@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 12:51:31 by julcalde          #+#    #+#             */
/*   Updated: 2025/07/12 15:56:44 by julcalde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"
#include "../include/mlx.h"

/*
	* This function rotates the player to the right by a certain angle defined 
	* by ROT_SPEED.
	* It updates the player's direction vector and camera plane based on the
	* rotation angle. The new direction is calculated using trigonometric 
	* functions (cosine and sine) to ensure the player rotates correctly in 
	* the game world.
	
	** If the right key is pressed, it updates the player's direction and 
	* camera plane.
	
	** If the new direction is valid, it updates the player's dir_x and dir_y 
	* coordinates.
	
	** If the new camera plane is valid, it updates the player's plane_x and 
	* plane_y coordinates.
	
	* @param game: Pointer to the game structure containing the player and 
	* rotation speed.
*/
void	rotate_player_right(t_game *game)
{
	double	old_dir_x;
	double	old_plane_x;

	if (mlx_is_key_down(game->mlx, RIGHT))
	{
		old_dir_x = game->player.dir_x;
		game->player.dir_x = game->player.dir_x * cos(ROT_SPEED) - \
			game->player.dir_y * sin(ROT_SPEED);
		game->player.dir_y = old_dir_x * sin(ROT_SPEED) + \
			game->player.dir_y * cos(ROT_SPEED);
		old_plane_x = game->player.plane_x;
		game->player.plane_x = game->player.plane_x * cos(ROT_SPEED) - \
			game->player.plane_y * sin(ROT_SPEED);
		game->player.plane_y = old_plane_x * sin(ROT_SPEED) + \
			game->player.plane_y * cos(ROT_SPEED);
	}
}

/*
	* This function rotates the player to the left by a certain angle defined 
	* by ROT_SPEED.
	* It updates the player's direction vector and camera plane based on the
	* rotation angle. The new direction is calculated using trigonometric 
	* functions (cosine and sine) to ensure the player rotates correctly in 
	* the game world.
	
	** If the left key is pressed, it updates the player's direction and 
	* camera plane.
	
	** If the new direction is valid, it updates the player's dir_x and dir_y 
	* coordinates.
	
	** If the new camera plane is valid, it updates the player's plane_x and 
	* plane_y coordinates.
	
	* @param game: Pointer to the game structure containing the player and 
	* rotation speed.
*/
void	rotate_player_left(t_game *game)
{
	double	old_dir_x;
	double	old_plane_x;

	if (mlx_is_key_down(game->mlx, LEFT))
	{
		old_dir_x = game->player.dir_x;
		game->player.dir_x = game->player.dir_x * cos(-ROT_SPEED) - \
			game->player.dir_y * sin(-ROT_SPEED);
		game->player.dir_y = old_dir_x * sin(-ROT_SPEED) + \
			game->player.dir_y * cos(-ROT_SPEED);
		old_plane_x = game->player.plane_x;
		game->player.plane_x = game->player.plane_x * cos(-ROT_SPEED) - \
			game->player.plane_y * sin(-ROT_SPEED);
		game->player.plane_y = old_plane_x * sin(-ROT_SPEED) + \
			game->player.plane_y * cos(-ROT_SPEED);
	}
}

/*
	* Checks if the left or right keys are pressed and rotates the player 
	* accordingly.
	* It calls the appropriate rotation functions based on the key state.
	* @param game: Pointer to the game structure containing the player and
	* rotation speed.
*/
void	rotate_player(t_game *game)
{
	if (mlx_is_key_down(game->mlx, LEFT))
		rotate_player_left(game);
	if (mlx_is_key_down(game->mlx, RIGHT))
		rotate_player_right(game);
}
