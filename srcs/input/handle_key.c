/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_key.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpehliva <hpehliva@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 08:58:35 by hpehliva          #+#    #+#             */
/*   Updated: 2025/07/21 16:42:47 by hpehliva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

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
