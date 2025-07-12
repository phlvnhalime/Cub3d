/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map01.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julcalde <julcalde@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 15:27:29 by julcalde          #+#    #+#             */
/*   Updated: 2025/07/12 19:22:19 by julcalde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static int	handle_map_line(t_game *game, char *line)
{
	if (!parse_map_line(game, line))
	{
		free(line);
		DEBUG_PRINT(RD"Failed to map parsing"RST);
		return (0);
	}
	return (1);
}

static int	handle_invalid_line(char *line)
{
	DEBUG_PRINT(RD"Invalid line in map section: %s\n"RST, line);
	free(line);
	return (0);
}

static int	process_map_lines(t_game *game, int fd)
{
	char	*line;

	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		if (!is_empty_line(line) && is_map_line(line))
		{
			if (!handle_map_line(game, line))
				return (0);
		}
		else if (!is_empty_line(line))
			return (handle_invalid_line(line));
		free(line);
	}
	return (1);
}

static int	validate_map_height(t_game *game)
{
	if (game->map.height == 0)
	{
		DEBUG_PRINT(RD"No map found in the file"RST);
		return (0);
	}
	return (1);
}

/*
	* Parses the map section of the game file. 
	* It reads lines from the file, processes valid map lines,
	* and validates the height of the map.
	* @param game Pointer to the game structure.
	* @param fd File descriptor of the opened game file.
	* @return 1 if parsing is successful, 0 otherwise.
*/
int	parse_map_section(t_game *game, int fd)
{
	if (!process_map_lines(game, fd))
		return (0);
	if (!validate_map_height(game))
		return (0);
	return (1);
}
