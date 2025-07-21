/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_01.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julcalde <julcalde@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 16:16:53 by hpehliva          #+#    #+#             */
/*   Updated: 2025/07/19 14:15:24 by julcalde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

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
			if (game->map.grid[y][x] == 'N' || game->map.grid[y][x] == 'S'
				|| game->map.grid[y][x] == 'E' || game->map.grid[y][x] == 'W')
			{
				if (player_count > 0)
				{
					DEBUG_PRINT(RD "Error: Multiple player positions found in \
					the map\n" RST);
					return (-1);
				}
				player_count++;
				spawn_char = game->map.grid[y][x];
				game->player.x = x + 0.5;
				game->player.y = y + 0.5;
				game->map.grid[y][x] = '0';
				DEBUG_PRINT(GRN "Player found at (%d, %d) --> (%.2f,%.2f) facing \
				'%c'\n" RST, x, y, game->player.x, game->player.y, spawn_char);
			}
			x++;
		}
		y++;
	}
	if (player_count != 1)
	{
		DEBUG_PRINT(RD "Invalid player count: %d (expected 1)\n" RST,
			player_count);
		return (0);
	}
	set_player_direction(game, spawn_char);
	game->player_found = 1;
	return (1);
}

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

int	check_map_walls(t_game *game)
{
	int		x;
	int		y;
	char	top_char;
	char	bottom_char;
	int		len;

	x = 0;
	while (x < game->map.width)
	{
		top_char = get_char_at(game->map.grid[0], x);
		if (top_char != '1' && top_char != ' ')
		{
			DEBUG_PRINT(RD "Map must be surrounded by walls (top) at x = %d\n"\
			RST, x);
			return (0);
		}
		bottom_char = get_char_at(game->map.grid[game->map.height - 1], x);
		if (bottom_char != '1' && bottom_char != ' ')
		{
			DEBUG_PRINT(RD "Map must be surrounded by walls (bottom) at x = %d\n"\
			RST, x);
			return (0);
		}
		x++;
	}
	y = 0;
	while (y < game->map.height)
	{
		if (game->map.grid[y][0] != '1' && game->map.grid[y][0] != ' ')
		{
			DEBUG_PRINT(RD "Map must be surrounded by walls (left) at y = %d\n"\
			RST, y);
			return (0);
		}
		len = ft_strlen(game->map.grid[y]);
		if (len > 1 && game->map.grid[y][len - 1] != ' '
			&& game->map.grid[y][len - 1] != '1')
		{
			DEBUG_PRINT(RD "Map must be surrounded by walls (right) at y = %d\n"\
			RST, y);
			return (0);
		}
		y++;
	}
	y = 1;
	while (y < game->map.height - 1)
	{
		x = 1;
		while (x < (int) ft_strlen(game->map.grid[y]) - 1)
		{
			if (game->map.grid[y][x] == '0')
			{
				if ((x > 0 && game->map.grid[y][x - 1] == ' ')
					|| ((x < game->map.width - 1) && game->map.grid[y][x
						+ 1] == ' ') || (y > 0 && game->map.grid[y
						- 1][x] == ' ') || (y < game->map.height - 1
						&& game->map.grid[y + 1][x] == ' '))
				{
					DEBUG_PRINT(RD "Map has a hole at (%d, %d)\n" RST, x, y);
					return (0);
				}
			}
			x++;
		}
		y++;
	}
	DEBUG_PRINT(GRN "Map walls are valid\n" RST);
	return (1);
}

int	parse_map_line(t_game *game, char *line)
{
	char	**new_grind;
	int		i;
	int		line_len;

	if (!line || !is_map_line(line))
	{
		DEBUG_PRINT(RD "Invalid map line: %s\n" RST, line);
		return (0);
	}
	line_len = ft_strlen(line);
	if (line_len > 0 && line[line_len - 1] == '\n')
	{
		line[line_len - 1] = '\0';
		line_len--;
	}
	new_grind = garbco_malloc(&game->garbco, sizeof(char *) * (game->map.height
				+ 1));
	if (!new_grind)
		return (0);
	i = 0;
	while (i < game->map.height)
	{
		new_grind[i] = game->map.grid[i];
		i++;
	}
	new_grind[game->map.height] = garbco_malloc(&game->garbco, sizeof(char)
			* (line_len + 1));
	if (!new_grind[game->map.height])
		return (0);
	ft_strlcpy(new_grind[game->map.height], line, line_len + 1);
	game->map.grid = new_grind;
	game->map.height++;
	if (line_len > game->map.width)
		game->map.width = line_len;
	DEBUG_PRINT(GRN "Map line added: %s (width: %d, height: %d)\n" RST, \
	line, game->map.width, game->map.height);
	return (1);
}
