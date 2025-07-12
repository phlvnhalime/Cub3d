/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_key.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julcalde <julcalde@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 08:58:35 by hpehliva          #+#    #+#             */
/*   Updated: 2025/07/12 13:26:48 by julcalde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"
#include "../include/mlx.h"

// #define MOVE_SPEED 0.08 // Adjust for your preferred speed
// #define ROT_SPEED 0.045 // Adjust for your preferred rotation speed

/*
	This function handles key events for player movement and rotation.
	It also handles the escape key to close the game window.
	- keydata: The key data structure containing information about the key event.
	- frame: Pointer to the game structure containing game state and player data.
	It checks for key presses and repeats, and updates the player's position	
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
