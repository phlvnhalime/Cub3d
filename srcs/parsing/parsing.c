/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julcalde <julcalde@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 20:35:21 by hpehliva          #+#    #+#             */
/*   Updated: 2025/07/22 23:09:53 by julcalde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

/*
** parse_file - Parses the configuration file for the game.
** This function opens the specified file, validates its contents, and
** extracts textures, colors, and the map section. It ensures that the file
** is correctly formatted and that all necessary components are present.
**
** @param game Pointer to the game structure that holds the parsed data.
** @param file The path to the configuration file to be parsed.
** @return 1 on success, 0 on failure.
*/
int	parse_file(t_game *game, char *file)
{
	int	fd;

	fd = open_and_validate_file(file);
	if (fd < 0)
		return (0);
	if (!parse_textures_and_colors(game, fd))
	{
		close(fd);
		error_exit_cleanup(game, "Failed to parse textures and colors");
	}
	if (!parse_map_section(game, fd))
	{
		close(fd);
		error_exit_cleanup(game, "Failed to parse map section");
	}
	close(fd);
	valid_map(game);
	if (!game->map_valid)
		error_exit_cleanup(game, "Map validation failed");
	return (1);
}
