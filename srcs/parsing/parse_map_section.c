/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_section.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julcalde <julcalde@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 15:50:30 by hpehliva          #+#    #+#             */
/*   Updated: 2025/07/19 11:33:28 by julcalde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

// int	parse_map_section(t_game *game, int fd)
// {
// 	char	*line;

// 	game->map_started = 1;
// 	while ((line = get_next_line(fd)))
// 	{
// 		if (!is_empty_line(line) && is_map_line(line))
// 		{
// 			if (!parse_map_line(game, line))
// 			{
// 				garbco_add(&game->garbco, line);
// 				return (0);
// 			}
// 		}
// 		else if (!is_empty_line(line))
// 		{
// 			garbco_add(&game->garbco, line);
// 			valid_error("Invalid line in map section", line);
// 		}
// 		free(line);
// 	}
// 	if (game->map.height == 0)
// 		return (0);
// 	return (1);
// }

static int	process_map_line(t_game *game, char *line)
{
	if (!is_empty_line(line) && is_map_line(line))
	{
		if (!parse_map_line(game, line))
		{
			garbco_add(&game->garbco, line);
			return (0);
		}
	}
	else if (!is_empty_line(line))
	{
		garbco_add(&game->garbco, line);
		valid_error("Invalid line in map section", line);
		return (0);
	}
	return (1);
}

int	parse_map_section(t_game *game, int fd)
{
	char	*line;

	game->map_started = 1;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		if (!process_map_line(game, line))
		{
			free(line);
			return (0);
		}
		free(line);
	}
	if (game->map.height == 0)
		return (0);
	return (1);
}
