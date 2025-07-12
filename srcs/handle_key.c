/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_key.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julcalde <julcalde@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 08:58:35 by hpehliva          #+#    #+#             */
/*   Updated: 2025/07/12 16:00:04 by julcalde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"
#include "../include/mlx.h"

/*
	* This function handles key events for the game.
	* It checks if the ESC key is pressed to close the game window.
	* If the action is a key press or repeat, it checks for movement keys 
	* (W, S, A, D) and calls the move_player function to update the player's 
	* position.
	* It also checks for rotation keys (LEFT, RIGHT) and calls the 
	* rotate_player function to update the player's direction.
	* @param keydata: The key data structure containing information about the key event.
	* @param frame: Pointer to the game structure containing the game state.
*/
void	handle_key(mlx_key_data_t keydata, void *frame)
{
	t_game	*game;

	game = (t_game *)frame;
	if (keydata.key == KEY_ESC && keydata.action == KEY_PRESS)
	{
		DEBUG_PRINT(RD"The Program is trying to closed\n"RST);
		mlx_close_window(game->mlx);
		return ;
	}
	if (keydata.action == KEY_PRESS || keydata.action == KEY_REPEAT)
	{
		if (keydata.key == W || keydata.key == S || keydata.key == A || \
			keydata.key == D)
		{
			move_player(game);
		}
		if (keydata.key == LEFT || keydata.key == RIGHT)
		{
			rotate_player(game);
		}
	}
}
