/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map04.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julcalde <julcalde@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 21:39:33 by julcalde          #+#    #+#             */
/*   Updated: 2025/07/12 21:39:43 by julcalde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

/*
	Finds the player's position in the map.
	- Scans the map grid for 'N', 'S', 'E', or 'W' characters.
	- If found, sets the player's position and direction.
	- Ensures only one player position is found.
	- Replaces the player character with '0' (empty space).
*/
int	find_player_position(t_game *game)
{
	int		x;
	int		y;
	int		player_count;
	char	spawn_char;

	player_count = 0;
	spawn_char = 0;
	y = 0;
	while (y < game->map.height)
	{
		x = 0;
		while (x < game->map.width && game->map.grid[y][x] != '\0')
		{
			if (game->map.grid[y][x] == 'N' || game->map.grid[y][x] == 'S' || \
				game->map.grid[y][x] == 'E' || game->map.grid[y][x] == 'W')
			{
				if (player_count > 0)
				{
					DEBUG_PRINT(RD"Error: Too many spawn locations\n"RST);
					return (-1);
				}
				player_count++;
				spawn_char = game->map.grid[y][x];
				game->player.x = x + 0.5;
				game->player.y = y + 0.5;
				game->map.grid[y][x] = '0';
				DEBUG_PRINT(GRN"Player found at (%d, %d) --> (%.2f, %.2f) facing \
				'%c'\n"RST, x, y, game->player.x, game->player.y, spawn_char);
			}
			x++;
		}
		y++;
	}
	if (player_count != 1)
	{
		DEBUG_PRINT(RD"Error: player count: %d (expected 1)\n"RST, player_count);
		return (0);
	}
	set_player_direction(game, spawn_char);
	game->player_found = 1;
	return (1);
}
