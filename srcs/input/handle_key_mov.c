/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_key_mov.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpehliva <hpehliva@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 13:44:56 by julcalde          #+#    #+#             */
/*   Updated: 2025/07/21 16:35:05 by hpehliva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static void	move_front(t_game *game)
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

static void	move_back(t_game *game)
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

static void	move_left(t_game *game)
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

static void	move_right(t_game *game)
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
