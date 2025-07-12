/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils00_parsing.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julcalde <julcalde@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 20:35:30 by hpehliva          #+#    #+#             */
/*   Updated: 2025/07/12 12:27:13 by julcalde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

/*
    Parsing validation:
    Is the map line readable? // TODO
        Space, tab, newline included.
    Is the map starting with the texture identifier? // TODO
        NO, SO, WE, EA
    Is the map has color identifiers? // TODO
        F, C
    Valid map characters: // TODO
        0, 1, N, S, E, W
*/

int	is_empty_line(char *line)
{
	while (*line)
	{
		if (*line != ' ' && *line != '\t' && *line != '\n')
			return (0); // Not an empty line
		line++;
	}
	return (1); // Empty line
}

int	texture_identifier(char *line)
{
	if (!line)
		return (0); // Null line is not valid
	if (ft_strncmp(line, "NO ", 3) == 0 || ft_strncmp(line, "SO ", 3) == 0 ||
		ft_strncmp(line, "WE ", 3) == 0 || ft_strncmp(line, "EA ", 3) == 0)
		return (1); // Valid texture identifier
	return (0); // Invalid texture identifier
}

int	is_color_identifier(char *line)
{
	if (!line)
		return (0); // Null line is not valid
	if (ft_strncmp(line, "F ", 2) == 0 || ft_strncmp(line, "C ", 2) == 0)
		return (1); // Valid color identifier
	return (0); // Invalid color identifier
}

int	is_valid_map_character(char c)
{
	return (c == '0' || c == '1' || c == 'N' || c == 'S' || c == 'E' || \
		c == 'W');
}

void	check_color_format(char *line)
{
	char	**colors;
	int		r;
	int		g;
	int		b;

	colors = ft_split(line, ',');
	if (ft_arraylen(colors) != 3)
	{
		ft_free_split(colors);
		error_exit("Invalid color format. Expected format: R,G,B");
	}
	r = ft_atoi(colors[0]);
	g = ft_atoi(colors[1]);
	b = ft_atoi(colors[2]);
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
	{
		ft_free_split(colors);
		error_exit("Color values must be in the range [0, 255]");
	}
	ft_free_split(colors);
}
