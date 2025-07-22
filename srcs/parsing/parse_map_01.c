/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_01.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julcalde <julcalde@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 16:16:53 by hpehliva          #+#    #+#             */
/*   Updated: 2025/07/22 22:22:51 by julcalde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

/*
** is_map_line - Checks if a line is a valid map line.
** It iterates through each character in the line,
** checking if it contains valid map characters (like '0', '1', '2', 'N', 'S',
** 'E', 'W').
** If it contains any valid map character, it returns 1.
** If it contains only spaces, tabs, or newlines, it returns 0.
** If it contains any invalid character, it returns 0.
**
** @param line: The line to be checked.
** @return 1 if the line is a valid map line, 0 otherwise.
*/
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

/*
** allocate_and_copy_grid - Allocates memory for a new grid
** and copies the existing grid into it.
** It allocates memory for the new grid based on the current map height,
** and then copies each row from the existing grid to the new grid.
**
** @param game: Pointer to the game structure containing the map.
** @param new_grid: Pointer to the new grid to be allocated and filled.
** @return 1 if the grid is allocated and copied successfully, 0 otherwise.
*/
int	allocate_and_copy_grid(t_game *game, char **new_grid)
{
	int	i;

	i = 0;
	while (i < game->map.height)
	{
		new_grid[i] = game->map.grid[i];
		i++;
	}
	return (1);
}

/*
** copy_new_line_to_grid - Copies a new line into the grid.
** It allocates memory for the new line in the grid,
** and then copies the content of the line into the newly allocated memory.
**
** @param game: Pointer to the game structure containing the map.
** @param new_grid: Pointer to the new grid where the line will be copied.
** @param line: The line to be copied into the grid.
** @param line_len: The length of the line to be copied.
** @return 1 if the line is copied successfully, 0 otherwise.
*/
int	copy_new_line_to_grid(t_game *game, char **new_grid, char *line,
		int line_len)
{
	new_grid[game->map.height] = garbco_malloc(&game->garbco, sizeof(char)
			* (line_len + 1));
	if (!new_grid[game->map.height])
		return (0);
	ft_strlcpy(new_grid[game->map.height], line, line_len + 1);
	return (1);
}

/*
** parse_map_line - Parses a line from the map section.
** It checks if the line is a valid map line,
** and if so, it allocates memory for a new grid,
** copies the existing grid into the new grid,
** and then copies the new line into the grid.
** It updates the map height and width accordingly.
**
** @param game: Pointer to the game structure containing the map.
** @param line: The line to be parsed.
** @return 1 if the line is parsed successfully, 0 otherwise.
*/
int	parse_map_line(t_game *game, char *line)
{
	char	**new_grid;
	int		line_len;

	if (!line || !is_map_line(line))
		return (0);
	line_len = ft_strlen(line);
	if (line_len > 0 && line[line_len - 1] == '\n')
	{
		line[line_len - 1] = '\0';
		line_len--;
	}
	new_grid = garbco_malloc(&game->garbco, sizeof(char *) * (game->map.height
				+ 1));
	if (!new_grid)
		return (0);
	if (!allocate_and_copy_grid(game, new_grid))
		return (0);
	if (!copy_new_line_to_grid(game, new_grid, line, line_len))
		return (0);
	game->map.grid = new_grid;
	game->map.height++;
	if (line_len > game->map.width)
		game->map.width = line_len;
	return (1);
}
