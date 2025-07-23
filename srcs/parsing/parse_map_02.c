/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_02.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpehliva <hpehliva@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 14:11:29 by hpehliva          #+#    #+#             */
/*   Updated: 2025/07/23 15:46:24 by hpehliva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

/*
** get_char_at - Returns the character at a specific position in a line.
** It checks if the line is NULL or if the position is out of bounds,
** returning a space character in those cases.
** Otherwise, it returns the character at the specified position.
**
** @param line: The line from which to get the character.
** @param position: The position in the line to get the character from.
** @return The character at the specified position, or a space character if
*/
char	get_char_at(char *line, int position)
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
** check_top_bottom_walls - Checks if the top and bottom walls of the map
** are valid.
** It iterates through the width of the map and checks if the characters
** at the top and bottom rows are either '1' or ' '.
** If any character is not valid, it returns 0.
** If all characters are valid, it returns 1.
**
** @param game: Pointer to the game structure containing the map.
** @return 1 if the top and bottom walls are valid, 0 otherwise.
*/
int	check_top_bottom_walls(t_game *game)
{
	int		x;
	char	top_char;
	char	bottom_char;

	x = 0;
	while (x < game->map.width)
	{
		top_char = get_char_at(game->map.grid[0], x);
		if (top_char != '1' && top_char != ' ')
			return (0);
		bottom_char = get_char_at(game->map.grid[game->map.height - 1], x);
		if (bottom_char != '1' && bottom_char != ' ')
			return (0);
		x++;
	}
	return (1);
}

/*
** check_left_right_walls - Checks if the left and right walls of the map
** are valid.
** It iterates through each row of the map and checks if the first and last
** characters are either '1' or ' '.
** If any character is not valid, it returns 0.
** If all characters are valid, it returns 1.
**
** @param game: Pointer to the game structure containing the map.
** @return 1 if the left and right walls are valid, 0 otherwise.
*/
int	check_left_right_walls(t_game *game)
{
	int	y;
	int	len;

	y = 0;
	while (y < game->map.height)
	{
		if (game->map.grid[y][0] != '1' && game->map.grid[y][0] != ' ')
			return (0);
		len = ft_strlen(game->map.grid[y]);
		if (len > 1 && game->map.grid[y][len - 1] != ' '
			&& game->map.grid[y][len - 1] != '1')
			return (0);
		y++;
	}
	return (1);
}

/*
** check_inner_zeros - Checks if there are any '0' characters
** in the inner part of the map that are adjacent to a space character.
** It iterates through the inner part of the map (excluding the borders)
** and checks if any '0' character has a space character adjacent to it
** (up, down, left, or right).
** If such a '0' character is found, it returns 0.
** If no such '0' character is found, it returns 1.
**
** @param game: Pointer to the game structure containing the map.
** @return 1 if no inner '0' characters are adjacent to spaces, 0 otherwise.
*/
int	check_inner_zeros(t_game *game)
{
	int	x;
	int	y;
	// int	row_len;

	y = 0;
	while (y < game->map.height)
	{
		x = 0;
		// row_len = ft_strlen(game->map.grid[y]);
		while (x < game->map.width)
		{
			if(get_char_at(game->map.grid[y], x) == '0' || get_char_at(game->map.grid[y], x) == 'N' || get_char_at(game->map.grid[y], x) == 'S' || get_char_at(game->map.grid[y], x) == 'E' || get_char_at(game->map.grid[y], x) == 'W')
			{
				if(get_char_at(game->map.grid[y], x - 1) == ' ' ||
				get_char_at(game->map.grid[y], x + 1) == ' ' ||
				(y > 0 && get_char_at(game->map.grid[y - 1], x) == ' ') ||
				(y < game->map.height - 1 && get_char_at(game->map.grid[y + 1], x) == ' '))
					return (0);
			}
			
			// if (game->map.grid[y][x] == '0')
			// {
			// 	if ((x > 0 && game->map.grid[y][x - 1] == ' ')
			// 		|| ((x < game->map.width - 1) && game->map.grid[y][x
			// 			+ 1] == ' ') || (y > 0 && game->map.grid[y
			// 			- 1][x] == ' ') || (y < game->map.height - 1
			// 			&& game->map.grid[y + 1][x] == ' '))
			// 		return (0);
			// }
			x++;
		}
		y++;
	}
	return (1);
}

/*
** check_map_walls - Checks if the walls of the map are valid.
** It calls the functions to check the top and bottom walls,
** the left and right walls, and the inner zeros.
** If any of these checks fail, it returns 0.
** If all checks pass, it returns 1.
**
** @param game: Pointer to the game structure containing the map.
** @return 1 if the walls are valid, 0 otherwise.
*/
int	check_map_walls(t_game *game)
{
	if (!check_top_bottom_walls(game))
		return (0);
	if (!check_left_right_walls(game))
		return (0);
	if (!check_inner_zeros(game))
		return (0);
	return (1);
}
