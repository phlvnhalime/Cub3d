/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_00.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julcalde <julcalde@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 15:50:30 by hpehliva          #+#    #+#             */
/*   Updated: 2025/07/22 22:20:24 by julcalde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

/*
** handle_map_line - Handles a line that is part of the map section.
** It checks if the map has already ended, and if so, it adds the line
** to the garbage collector and raises an error.
** If the map has not ended, it attempts to parse the line as a map line.
** If the parsing fails, it adds the line to the garbage collector
** and returns 0, indicating an error.
** If the parsing is successful, it returns 1.
**
** @param game: Pointer to the game structure.
** @param line: The line to be processed.
** @param map_started: Pointer to indicate if the map has started.
** @param map_ended: Pointer to indicate if the map has ended.
** @return 1 if the line is valid and parsed successfully, 0 otherwise.
*/
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

/*
** handle_empty_line - Handles an empty line in the map section.
** If the map has already started, it sets the map_ended flag to 1,
** indicating that the map section has ended.
** This function is called when an empty line is encountered
** after the map has started, signaling the end of the map section.
**
** @param map_started: Pointer to indicate if the map has started.
** @param map_ended: Pointer to indicate if the map has ended.
*/
static void	handle_empty_line(int *map_started, int *map_ended)
{
	if (*map_started)
		*map_ended = 1;
}

/*
** handle_invalid_line - Handles a line that is not valid in the map section.
** It adds the line to the garbage collector and raises an error.
** If the map has already started, it raises an error indicating
** that invalid content was found after the map section.
** If the map has not started, it raises an error indicating
** that the line is invalid in the map section.
**
** @param game: Pointer to the game structure.
** @param line: The invalid line to be processed.
** @param map_started: Pointer to indicate if the map has started.
*/
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

/*
** validate_map_block - Validates a block of the map section.
** It checks if the line is a map line, an empty line, or an invalid line.
** If it is a map line, it calls handle_map_line to process it.
** If it is an empty line,
	it calls handle_empty_line to mark the end of the map.
** If it is an invalid line, it calls handle_invalid_line to handle the error.
** It returns 1 if the block is valid, or 0 if an error occurs.
**
** @param game: Pointer to the game structure.
** @param line: The line to be validated.
** @param map_started: Pointer to indicate if the map has started.
** @param map_ended: Pointer to indicate if the map has ended.
** @return 1 if the block is valid, 0 if an error occurs.
*/
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

/*
** parse_map_section - Parses the map section of the game.
** It reads lines from the file descriptor until the end of the file.
** It initializes the map_started flag to 1, indicating that the map section
** has started.
** It processes each line using validate_map_block to check if it is a valid
** map line,
** an empty line, or an invalid line.
** If the map height is 0 after processing all lines, it returns 0, indicating
** an error.
** If the map section is valid, it returns 1.
**
** @param game: Pointer to the game structure.
** @param fd: The file descriptor to read the map section from.
** @return 1 if the map section is valid, 0 if an error occurs.
*/
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
