/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_02.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpehliva <hpehliva@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 14:11:29 by hpehliva          #+#    #+#             */
/*   Updated: 2025/07/21 14:37:38 by hpehliva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

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

int	check_inner_zeros(t_game *game)
{
	int	x;
	int	y;
	int	row_len;

	y = 1;
	while (y < game->map.height - 1)
	{
		x = 1;
		row_len = ft_strlen(game->map.grid[y]);
		while (x < row_len - 1)
		{
			if (game->map.grid[y][x] == '0')
			{
				if ((x > 0 && game->map.grid[y][x - 1] == ' ')
					|| ((x < game->map.width - 1) && game->map.grid[y][x
						+ 1] == ' ') || (y > 0 && game->map.grid[y
						- 1][x] == ' ') || (y < game->map.height - 1
						&& game->map.grid[y + 1][x] == ' '))
					return (0);
			}
			x++;
		}
		y++;
	}
	return (1);
}

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
