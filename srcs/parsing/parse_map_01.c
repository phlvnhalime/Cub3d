/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_01.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpehliva <hpehliva@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 16:16:53 by hpehliva          #+#    #+#             */
/*   Updated: 2025/07/21 16:41:32 by hpehliva         ###   ########.fr       */
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
