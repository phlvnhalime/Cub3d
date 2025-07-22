/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_00.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julcalde <julcalde@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 15:50:30 by hpehliva          #+#    #+#             */
/*   Updated: 2025/07/22 20:09:28 by julcalde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static int	handle_map_line(t_game *game, char *line, int *map_started,
		int *map_ended)
{
	if (*map_ended)
	{
		garbco_add(&game->garbco, line);
		valid_error("Error: chunks of map cannot be separated", line);
	}
	*map_started = 1;
	if (!parse_map_line(game, line))
	{
		garbco_add(&game->garbco, line);
		return (0);
	}
	return (1);
}

static void	handle_empty_line(int *map_started, int *map_ended)
{
	if (*map_started)
		*map_ended = 1;
}

static void	handle_invalid_line(t_game *game, char *line, int *map_started)
{
	garbco_add(&game->garbco, line);
	if (*map_started)
	{
		valid_error("Invalid content found after map section", line);
	}
	else
	{
		valid_error("Invalid line map section", line);
	}
}

int	validate_map_block(t_game *game, char *line, int *map_started,
		int *map_ended)
{
	if (is_map_line(line))
	{
		if (!handle_map_line(game, line, map_started, map_ended))
			return (0);
	}
	else if (is_empty_line(line))
	{
		handle_empty_line(map_started, map_ended);
	}
	else
	{
		handle_invalid_line(game, line, map_started);
	}
	return (1);
}

int	parse_map_section(t_game *game, int fd)
{
	char	*line;
	int		map_started;
	int		map_ended;

	line = NULL;
	map_started = 0;
	map_ended = 0;
	game->map_started = 1;
	line = get_next_line(fd);
	while (line != NULL)
	{
		if (!validate_map_block(game, line, &map_started, &map_ended))
		{
			free(line);
			return (0);
		}
		free(line);
		line = get_next_line(fd);
	}
	if (game->map.height == 0)
		return (0);
	return (1);
}
