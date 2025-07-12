/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils00_parsing.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julcalde <julcalde@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 20:35:30 by hpehliva          #+#    #+#             */
/*   Updated: 2025/07/12 15:18:40 by julcalde         ###   ########.fr       */
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

/*
	Checks if the line is empty.
	An empty line is defined as a line that contains only spaces, tabs, or 
	newlines.
	Returns 1 if the line is empty, 0 otherwise.
*/
int	is_empty_line(char *line)
{
	while (*line)
	{
		if (*line != ' ' && *line != '\t' && *line != '\n')
			return (0);
		line++;
	}
	return (1);
}

/*
	Checks if the line starts with a valid texture identifier.
	Valid identifiers are:
	- "NO " for North texture
	- "SO " for South texture
	- "WE " for West texture
	- "EA " for East texture
	Returns 1 if the line is a valid texture identifier, 0 otherwise.
*/
int	texture_identifier(char *line)
{
	if (!line)
		return (0);
	if (ft_strncmp(line, "NO ", 3) == 0 || ft_strncmp(line, "SO ", 3) == 0 ||
		ft_strncmp(line, "WE ", 3) == 0 || ft_strncmp(line, "EA ", 3) == 0)
		return (1);
	return (0);
}

/*
	Checks if the line is a valid color identifier.
	Valid identifiers are:
	- "F " for floor color
	- "C " for ceiling color
	Returns 1 if the line is a valid color identifier, 0 otherwise.
*/
int	is_color_identifier(char *line)
{
	if (!line)
		return (0);
	if (ft_strncmp(line, "F ", 2) == 0 || ft_strncmp(line, "C ", 2) == 0)
		return (1);
	return (0);
}

/*
	Checks if the character is a valid map character.
	Valid characters are:
	- '0' for empty space
	- '1' for wall
	- 'N', 'S', 'E', 'W' for player spawn directions
	Returns 1 if the character is valid, 0 otherwise.
*/
int	is_valid_map_character(char c)
{
	return (c == '0' || c == '1' || c == 'N' || c == 'S' || c == 'E' || \
		c == 'W');
}

/*
	Checks if the color format in the line is valid.
	The expected format is "R,G,B" where R, G, and B are integers in the range 
	[0, 255].
	If the format is invalid or the values are out of range, it exits with an 
	error message.
	- line: The line containing the color values
*/
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
