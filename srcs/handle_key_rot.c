/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_key_rot.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julcalde <julcalde@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 12:51:31 by julcalde          #+#    #+#             */
/*   Updated: 2025/07/12 13:25:54 by julcalde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"
#include "../include/mlx.h"

/*
	This function rotates the player to the right by a certain angle defined 
	by ROT_SPEED.
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
	This function rotates the player to the left by a certain angle defined 
	by ROT_SPEED.
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
	Checks if the left or right keys are pressed and rotates the player accordingly.
	It calls the appropriate rotation functions based on the key state.
*/
void	rotate_player(t_game *game)
{
	if (mlx_is_key_down(game->mlx, LEFT))
		rotate_player_left(game);
	if (mlx_is_key_down(game->mlx, RIGHT))
		rotate_player_right(game);
}
