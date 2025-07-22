/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_key.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julcalde <julcalde@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 08:58:35 by hpehliva          #+#    #+#             */
/*   Updated: 2025/07/22 20:28:18 by julcalde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

/*
** handle_key - Handles key events for player movement and rotation.
** This function checks for key presses and updates the player's position or
** rotation based on the key pressed. It also handles the escape key to close
** the game window.
**
** @param keydata Key data structure containing information about the key event.
** @param frame Pointer to the game structure containing player and map data.
*/
void	handle_key(mlx_key_data_t keydata, void *frame)
{
	t_game	*game;

	game = (t_game *)frame;
	if (keydata.key == KEY_ESC && keydata.action == KEY_PRESS)
	{
		mlx_close_window(game->mlx);
		return ;
	}
	if (keydata.action == KEY_PRESS || keydata.action == KEY_REPEAT)
	{
		if (keydata.key == W || keydata.key == S || keydata.key == A
			|| keydata.key == D)
		{
			move_player(game);
		}
		if (keydata.key == LEFT || keydata.key == RIGHT)
		{
			rotate_player(game);
		}
	}
}
