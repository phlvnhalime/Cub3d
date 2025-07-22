/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_player_pos.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julcalde <julcalde@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 13:40:57 by hpehliva          #+#    #+#             */
/*   Updated: 2025/07/22 23:06:16 by julcalde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

/*
** check_player_spawn - Checks if a player spawn character ('N', 'S', 'E', 'W')
** exists in a specific row of the map.
** It iterates through the row, counting the number of player spawn characters.
** If it finds a player spawn character, it sets the player's position
** and direction based on the spawn character.
** If it finds more than one player spawn character, it returns -1.
** If it finds exactly one player spawn character, it updates the player's
** position and returns 1.
** If it finds no player spawn character, it returns 0.
**
** @param game: Pointer to the game structure containing the map and player.
** @param y: The row index to check for player spawn characters.
** @param spawn_char: Pointer to store the spawn character found in the row.
** @return 1 if a player spawn character is found and set successfully,
*/
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

/*
** find_player_position - Finds the player's position in the map.
** It iterates through each row of the map,
** checking for a player spawn character ('N', 'S', 'E', 'W').
** If it finds a valid spawn character, it sets the player's position
** and direction based on the spawn character.
** If it finds more than one player spawn character, it returns 0.
** If it finds no player spawn character, it returns -1.
** If it finds exactly one player spawn character, it sets the player's
** direction and returns 1.
** If an error occurs during the check, it returns -1.
**
** @param game: Pointer to the game structure containing the map and player.
** @return 1 if the player position is found and set successfully,
*/
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
