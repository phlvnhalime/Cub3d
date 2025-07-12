/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map03.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julcalde <julcalde@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 20:49:37 by julcalde          #+#    #+#             */
/*   Updated: 2025/07/12 21:37:29 by julcalde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static int	validate_map_line(char *line)
{
	if (!line || !is_map_line(line))
	{
		DEBUG_PRINT(RD"Invalid map line: %s\n"RST, line);
		return (0);
	}
	return (1);
}

static char	**allocate_new_grid(t_game *game, int line_len)
{
	char	**new_grid;
	int		i;

	new_grid = garbco_malloc(&game->garbco, sizeof(char *) * \
	(game->map.height + 1));
	if (!new_grid)
		return (NULL);
	i = 0;
	while (i < game->map.height)
	{
		new_grid[i] = game->map.grid[i];
		i++;
	}
	new_grid[game->map.height] = garbco_malloc(&game->garbco, \
	sizeof(char) * (line_len + 1));
	if (!new_grid[game->map.height])
		return (NULL);
	return (new_grid);
}

static void	update_map_dimensions(t_game *game, char *line, int line_len)
{
	ft_strlcpy(game->map.grid[game->map.height], line, line_len + 1);
	if (game->map.grid)
		garbco_remove(&game->garbco, game->map.grid);
	game->map.height++;
	if (line_len > game->map.width)
		game->map.width = line_len;
	DEBUG_PRINT(GRN"Map line added: %s (width: %d, height: %d)\n"RST, line, \
	game->map.width, game->map.height);
}

/*
	* Parses a line of the map and updates the game map structure.
	* - Validates the line.
	* - Allocates memory for the new grid.
	* - Updates the map dimensions.
	* - Returns 1 on success, 0 on failure.
	* @param game Pointer to the game structure.
	* @param line The line to be parsed.
	* @return 1 on success, 0 on failure.
*/
int	parse_map_line(t_game *game, char *line)
{
	int		line_len;
	char	**new_grid;

	if (!validate_map_line(line))
		return (0);
	line_len = ft_strlen(line);
	if (line_len > 0 && line[line_len - 1] == '\n')
	{
		line[line_len - 1] = '\0';
		line_len--;
	}
	new_grid = allocate_new_grid(game, line_len);
	if (!new_grid)
		return (0);
	game->map.grid = new_grid;
	update_map_dimensions(game, line, line_len);
	return (1);
}

/********************/
/* ORIGINAL version */
/********************/

// int	parse_map_line(t_game *game, char *line)
// {
// 	char	**new_grind;
// 	int		line_len;

	// if (!line || !is_map_line(line))
	// {
	// 	DEBUG_PRINT(RD"Invalid map line: %s\n"RST, line);
	// 	return (0);
	// }

	// line_len = ft_strlen(line);
	// if (line_len > 0 && line[line_len - 1] == '\n')
	// {
	// 	line[line_len - 1] = '\0';
	// 	line_len--;
	// }
	// new_grind = garbco_malloc(&game->garbco, 
		// sizeof(char *) * (game->map.height + 1));
	// if (!new_grind)
	// 	return (0);
	// i = 0;
	// while (i < game->map.height)
	// {
	// 	new_grind[i] = game->map.grid[i];
	// 	i++;
	// }
	// new_grind[game->map.height] = garbco_malloc(&game->garbco, 
		// sizeof(char) * (line_len + 1));
	// if (!new_grind[game->map.height])
	// 	return (0);

	// ft_strlcpy(new_grind[game->map.height], line, line_len + 1);
	// if (game->map.grid)
	// 	garbco_remove(&game->garbco, game->map.grid);
	// game->map.grid = new_grind;
	// game->map.height++;
	// if (line_len > game->map.width)
	// 	game->map.width = line_len;
	// DEBUG_PRINT(GRN"Map line added: %s (width: %d, height: 
		// %d)\n"RST, line, game->map.width, game->map.height);
	// return (1);
// }
