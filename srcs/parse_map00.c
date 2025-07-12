/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map00.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julcalde <julcalde@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 16:16:53 by hpehliva          #+#    #+#             */
/*   Updated: 2025/07/12 21:34:08 by julcalde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

/*
	Returns the character at the specified position in the line.
	- If the position is out of bounds, returns a space character.
	- If the line is NULL, also returns a space character.
*/
static char	get_char_at(char *line, int position)
{
	int	len;

	len = ft_strlen(line);
	if (!line)
		return (' ');
	if (position >= len || position < 0)
		return (' ');
	return (line[position]);
}

/*
	Checks if the map is surrounded by walls.
	- Validates the top and bottom walls.
	- Validates the left and right walls.
	- Checks for holes in the map (i.e., '0's surrounded by spaces).
	- Returns 1 if valid, 0 if invalid.
*/
int	check_map_walls(t_game *game)
{
	int		x;
	int		y;
	char	top_char;
	char	bottom_char;
	int		row_len;

	x = 0;
	while (x < game->map.width)
	{
		top_char = get_char_at(game->map.grid[0], x);
		if (top_char != '1' && top_char != ' ')
		{
			DEBUG_PRINT(RD"Walls missing (top) at x = %d\n"RST, x);
			return (0);
		}
		bottom_char = get_char_at(game->map.grid[game->map.height - 1], x);
		if (bottom_char != '1' && bottom_char != ' ')
		{
			DEBUG_PRINT(RD"Walls missing (bottom) at x = %d\n"RST, x);
			return (0);
		}
		x++;
	}
	y = 0;
	while (y < game->map.height)
	{
		if (game->map.grid[y][0] != '1' && game->map.grid[y][0] != ' ')
		{
			DEBUG_PRINT(RD"Walls missing (left) at y = %d\n"RST, y);
			return (0);
		}
		if (ft_strlen(game->map.grid[y]) > 1 && \
		game->map.grid[y][ft_strlen(game->map.grid[y] - 1)] != ' ' && \
		game->map.grid[y][ft_strlen(game->map.grid[y] - 1)] != '1')
		{
			DEBUG_PRINT(RD"Walls missing (right) at y = %d\n"RST, y);
			return (0);
		}
		y++;
	}
	y = 1;
	while (y < game->map.height - 1)
	{
		x = 1;
		row_len = ft_strlen(game->map.grid[y]);
		while (x < row_len -1)
		{
			if (game->map.grid[y][x] == '0')
			{
				if ((x > 0 && game->map.grid[y][x - 1] == ' ') || \
				((x < game->map.width - 1) && game->map.grid[y][x + 1] == ' ') \
				|| (y > 0 && game->map.grid[y - 1][x] == ' ') || \
				(y < game->map.height - 1 && game->map.grid[y + 1][x] == ' '))
				{
					DEBUG_PRINT(RD"Map has a hole at (%d, %d)\n"RST, x, y);
					return (0);
				}
			}
			x++;
		}
		y++;
	}
	DEBUG_PRINT(GRN"Map walls are valid\n"RST);
	return (1);
}

/*
	Checks if the character is a valid map character.
	Valid characters are '0', '1', 'N', 'S', 'E', 'W', space, and tab.
*/
int	is_map_line(char *line)
{
	int	i;
	int	has_map_char;

	has_map_char = 0;

	if (!line)
		return (0);
	i = 0;
	while (line[i])
	{
		if (is_valid_map_character(line[i]))
			has_map_char = 1;
		else if (line[i] != ' ' && line[i] != '\t' && line[i] != '\n')
			return (0);
		i++;
	}
	return (has_map_char);
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

/*
	Validates the map.
	- Checks if the map is too small (less than 3x3).
	- Finds the player position and sets the player's direction.
	- Checks if the map walls are valid.
	- Sets the map_valid flag accordingly.
*/
void	valid_map(t_game *game)
{
	if (game->map.height < 3 || game->map.width < 3)
	{
		DEBUG_PRINT(RD"Map is too small (width: %d, height: %d)\n"RST, \
			game->map.width, game->map.height);
		game->map_valid = 0;
		return ;
	}
	if (!find_player_position(game))
	{
		DEBUG_PRINT(RD"Player position not found or invalid\n"RST);
		game->map_valid = 0;
		return ;
	}
	if (!check_map_walls(game))
	{
		DEBUG_PRINT(RD"Map walls are not valid\n"RST);
		game->map_valid = 0;
		return ;
	}
	game->map_valid = 1;
	DEBUG_PRINT(GRN"Map is valid\n"RST);
}
