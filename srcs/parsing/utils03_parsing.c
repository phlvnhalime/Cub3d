/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils03_parsing.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpehliva <hpehliva@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 23:31:00 by hpehliva          #+#    #+#             */
/*   Updated: 2025/07/24 10:29:08 by hpehliva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

/*
** lenght_encountered - Checks if the length of the map is consistent.
** This function checks if the length of the map is consistent.
** It checks if the length of the map is consistent.
**
** @param game: Pointer to the game structure.
*/

int	lenght_encountered(t_game *game)
{
	int	y;
	int	current_len;
	int	prev_len;

	current_len = 0;
	prev_len = 0;
	y = 1;
	while (y < game->map.height)
	{
		current_len = ft_strlen(game->map.grid[y]);
		prev_len = ft_strlen(game->map.grid[y - 1]);
		if (!compare_lengths(game, current_len, prev_len, y))
			return (0);
		prev_len = current_len;
		y++;
	}
	return (1);
}

/*
** check_rotation - Checks if the rotation is valid.
** This function checks if the rotation is valid.
** It checks if the rotation is valid.
**
** @param game: Pointer to the game structure.
*/

int	check_rotation(t_game *game, int x, int y)
{
	char	left;
	char	right;
	char	up;
	char	down;

	left = get_char_at(game->map.grid[y], x - 1);
	right = get_char_at(game->map.grid[y], x + 1);
	up = get_char_at(game->map.grid[y - 1], x);
	down = get_char_at(game->map.grid[y + 1], x);
	if ((left == ' ' || right == ' ' || (y > 0 && up == ' ')
			|| (y < game->map.height - 1 && down == ' ')))
		return (0);
	return (1);
}

/*
** compare_lengths
	- Compares the lengths of the current and previous lines in the map.
** It checks if the current line is longer than the previous line and if so,
** it checks if the characters in the current line are valid.
**
** @param game: Pointer to the game structure.
*/

int	compare_lengths(t_game *game, int curr_len, int prev_len, int y)
{
	int		x;
	char	curr;

	x = 0;
	if (curr_len > prev_len)
	{
		x = prev_len;
		while (x < curr_len)
		{
			curr = game->map.grid[y][x];
			if (curr == '0' || curr == 'N' || curr == 'S' || curr == 'E'
				|| curr == 'W')
				return (0);
			if (curr == '1')
			{
				if (x > 0 && (game->map.grid[y][x - 1] == '0'
						|| game->map.grid[y][x - 1] == 'N'
						|| game->map.grid[y][x - 1] == 'S'
						|| game->map.grid[y][x - 1] == 'E'
						|| game->map.grid[y][x - 1] == 'W'))
					return (0);
			}
			x++;
		}
	}
	return (1);
}
