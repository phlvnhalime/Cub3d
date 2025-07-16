/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_key_rot.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julcalde <julcalde@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 13:45:36 by julcalde          #+#    #+#             */
/*   Updated: 2025/07/13 13:54:17 by julcalde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static void	rotate_player_left(t_game *game)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = game->player.dir_x;
	game->player.dir_x = game->player.dir_x * cos(-ROT_SPEED) \
		- game->player.dir_y * sin(-ROT_SPEED);
	game->player.dir_y = old_dir_x * sin(-ROT_SPEED) \
		+ game->player.dir_y * cos(-ROT_SPEED);
	old_plane_x = game->player.plane_x;
	game->player.plane_x = game->player.plane_x * cos(-ROT_SPEED) \
		- game->player.plane_y * sin(-ROT_SPEED);
	game->player.plane_y = old_plane_x * sin(-ROT_SPEED) \
		+ game->player.plane_y * cos(-ROT_SPEED);
}

static void	rotate_player_right(t_game *game)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = game->player.dir_x;
	game->player.dir_x = game->player.dir_x * cos(ROT_SPEED) \
		- game->player.dir_y * sin(ROT_SPEED);
	game->player.dir_y = old_dir_x * sin(ROT_SPEED) \
		+ game->player.dir_y * cos(ROT_SPEED);
	old_plane_x = game->player.plane_x;
	game->player.plane_x = game->player.plane_x * cos(ROT_SPEED) \
		- game->player.plane_y * sin(ROT_SPEED);
	game->player.plane_y = old_plane_x * sin(ROT_SPEED) \
		+ game->player.plane_y * cos(ROT_SPEED);
}

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
