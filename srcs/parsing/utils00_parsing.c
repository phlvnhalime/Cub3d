/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils00_parsing.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julcalde <julcalde@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 20:35:30 by hpehliva          #+#    #+#             */
/*   Updated: 2025/07/22 23:50:55 by julcalde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

/*
** is_empty_line - Checks if a line is empty or contains only whitespace.
** This function iterates through the characters in the line and returns
** 1 if the line is empty or contains only spaces, tabs, or newline characters.
** It returns 0 if the line contains any non-whitespace characters.
**
** @param line The line to check.
** @return 1 if the line is empty or contains only whitespace, 0 otherwise.
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
** texture_identifier - Checks if a line is a texture identifier.
** This function checks if the line starts with "NO ", "SO ", "WE ", or "EA ",
** which are the identifiers for textures in the configuration file.
**
** @param line The line to check.
** @return 1 if the line is a texture identifier, 0 otherwise.
*/
int	texture_identifier(char *line)
{
	if (!line)
		return (0);
	if (ft_strncmp(line, "NO ", 3) == 0 || ft_strncmp(line, "SO ", 3) == 0
		|| ft_strncmp(line, "WE ", 3) == 0 || ft_strncmp(line, "EA ", 3) == 0)
		return (1);
	return (0);
}

/*
** is_color_identifier - Checks if a line is a color identifier.
** This function checks if the line starts with "F " or "C ", which are
** the identifiers for floor and ceiling colors in the configuration file.
**
** @param line The line to check.
** @return 1 if the line is a color identifier, 0 otherwise.
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
** is_valid_map_character - Checks if a character is a valid map character.
** This function verifies if the character is one of the valid map characters:
** '0', '1', 'N', 'S', 'E', or 'W'. It is used to validate the contents of
** the map section in the configuration file.
**
** @param c The character to check.
** @return 1 if the character is valid, 0 otherwise.
*/
int	is_valid_map_character(char c)
{
	return (c == '0' || c == '1' || c == 'N' || c == 'S' || c == 'E'
		|| c == 'W');
}

/*
** check_color_format - Validates the format of a color line.
** This function checks if the line contains exactly three comma-separated
** values representing RGB color components. It ensures that each component
** is an integer within the range of 0 to 255. If the format is invalid or
** the values are out of range, it exits the program with an error message.
**
** @param line The line containing the color values in the format <R,G,B>.
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
		error_exit("Invalid color format. Expected format: <R,G,B>");
	}
	r = ft_atoi(colors[0]);
	g = ft_atoi(colors[1]);
	b = ft_atoi(colors[2]);
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
	{
		ft_free_split(colors);
		error_exit("Color values must be in the range [0 - 255]");
	}
	ft_free_split(colors);
}
