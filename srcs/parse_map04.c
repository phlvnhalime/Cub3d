/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map04.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julcalde <julcalde@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 21:39:33 by julcalde          #+#    #+#             */
/*   Updated: 2025/07/12 22:18:46 by julcalde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

/*
	* Handles the case where the player count is invalid.
	* @returns
	* -1 if there are too many spawn locations.
	*
	* 0 if the player count is not exactly 1.
	*
	* 1 if the player count is valid (exactly 1).
*/
static int	handle_invalid_pcount(int player_count)
{
	if (player_count > 1)
	{
		DEBUG_PRINT(RD"Error: Too many spawn locations\n"RST);
		return (-1);
	}
	else if (player_count != 1)
	{
		DEBUG_PRINT(RD"Error: player count: %d (expected 1)\n"RST, player_count);
		return (0);
	}
	return (1);
}

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
				handle_invalid_pcount(player_count);
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
	handle_invalid_pcount(player_count);
	set_player_direction(game, spawn_char);
	game->player_found = 1;
	return (1);
}
