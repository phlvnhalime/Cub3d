/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpehliva <hpehliva@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 20:35:21 by hpehliva          #+#    #+#             */
/*   Updated: 2025/07/21 16:31:52 by hpehliva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

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
