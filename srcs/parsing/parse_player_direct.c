/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_player_direct.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpehliva <hpehliva@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 13:38:02 by hpehliva          #+#    #+#             */
/*   Updated: 2025/07/21 14:10:26 by hpehliva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static void	set_north_direction(t_game *game)
{
	game->player.dir_x = 0.0;
	game->player.dir_y = -1.0;
	game->player.plane_x = 0.66;
	game->player.plane_y = 0.0;
	game->player.spawn_dir = 90.0;
}

static void	set_south_direction(t_game *game)
{
	game->player.dir_x = 0.0;
	game->player.dir_y = 1.0;
	game->player.plane_x = -0.66;
	game->player.plane_y = 0.0;
	game->player.spawn_dir = 270.0;
}

static void	set_east_direction(t_game *game)
{
	game->player.dir_x = 1.0;
	game->player.dir_y = 0.0;
	game->player.plane_x = 0.0;
	game->player.plane_y = 0.66;
	game->player.spawn_dir = 0.0;
}

static void	set_west_direction(t_game *game)
{
	game->player.dir_x = -1.0;
	game->player.dir_y = 0.0;
	game->player.plane_x = 0.0;
	game->player.plane_y = -0.66;
	game->player.spawn_dir = 180.0;
}

void	set_player_direction(t_game *game, char spawn_char)
{
	game->player.spawn_char = spawn_char;
	if (spawn_char == 'N')
		set_north_direction(game);
	else if (spawn_char == 'S')
		set_south_direction(game);
	else if (spawn_char == 'E')
		set_east_direction(game);
	else if (spawn_char == 'W')
		set_west_direction(game);
}
