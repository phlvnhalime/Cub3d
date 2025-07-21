/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_player_pos.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpehliva <hpehliva@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 13:40:57 by hpehliva          #+#    #+#             */
/*   Updated: 2025/07/21 13:56:13 by hpehliva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static int	check_player_spawn(t_game *game, int y, char *spawn_char)
{
	int	x;
	int	player_count;

	x = 0;
	player_count = 0;
	while (x < game->map.width && game->map.grid[y][x] != '\0')
	{
		if (game->map.grid[y][x] == 'N' || game->map.grid[y][x] == 'S'
			|| game->map.grid[y][x] == 'E' || game->map.grid[y][x] == 'W')
		{
			if (player_count > 0)
				return (-1);
			player_count++;
			*spawn_char = game->map.grid[y][x];
			game->player.x = x + 0.5;
			game->player.y = y + 0.5;
			game->map.grid[y][x] = '0';
		}
		x++;
	}
	return (player_count);
}

int	find_player_position(t_game *game)
{
	int		y;
	int		player_count;
	char	spawn_char;
	int		res;

	y = 0;
	player_count = 0;
	spawn_char = 0;
	while (y < game->map.height)
	{
		res = check_player_spawn(game, y, &spawn_char);
		if (res == -1)
			return (-1);
		player_count += res;
		y++;
	}
	if (player_count != 1)
		return (0);
	set_player_direction(game, spawn_char);
	game->player_found = 1;
	return (1);
}
