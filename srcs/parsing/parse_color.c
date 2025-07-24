/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpehliva <hpehliva@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 14:01:21 by hpehliva          #+#    #+#             */
/*   Updated: 2025/07/24 10:30:00 by hpehliva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

/*
** valid_rgb_format - Validates if the RGB values are within the range of 0
** to 255.
** It checks each value and returns 0 if any value is out of range,
** otherwise returns 1.
**
** @param r: Red component of the color.
** @param g: Green component of the color.
** @param b: Blue component of the color.
** @return 1 if all values are valid, 0 otherwise.
*/
int	valid_rgb_format(int r, int g, int b)
{
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		return (0);
	return (1);
}

/*
** set_color_values - Sets the RGB values and hex representation
** for the floor or ceiling color in the game structure.
** It takes the game structure,
	an identifier ('F' for floor or 'C' for ceiling),
** and an array of RGB values.
** It updates the corresponding color structure with the RGB values
** and calculates the hex value.
**
** @param game: Pointer to the game structure.
** @param identifier: 'F' for floor or 'C' for ceiling.
** @param rgb_arr: Array containing the RGB values.
*/
void	set_color_values(t_game *game, char identifier, int rgb_arr[3])
{
	if (identifier == 'F')
	{
		game->floor_color.r = rgb_arr[0];
		game->floor_color.g = rgb_arr[1];
		game->floor_color.b = rgb_arr[2];
		game->floor_color.hex = (rgb_arr[0] << 16) | (rgb_arr[1] << 8) | rgb_arr[2];
	}
	else if (identifier == 'C')
	{
		game->ceiling_color.r = rgb_arr[0];
		game->ceiling_color.g = rgb_arr[1];
		game->ceiling_color.b = rgb_arr[2];
		game->ceiling_color.hex = (rgb_arr[0] << 16) | (rgb_arr[1] << 8) | rgb_arr[2];
	}
	game->color_count++;
}

/*
** validate_color_input - Validates the input line for color definitions.
** It checks if the line starts with a valid color identifier ('F' or 'C'),
** splits the line into components, and checks if the RGB values are provided
** in the correct format (three comma-separated values).
** If the input is valid, it returns 1 and sets the split_line and rgb pointers.
** If the input is invalid, it frees any allocated memory and returns 0.
**
** @param line: The input line containing the color definition.
** @param split_line: Pointer to store the split line components.
** @param rgb: Pointer to store the RGB values split from the line.
** @return 1 if the input is valid, 0 otherwise.
*/
static int	validate_color_input(char *line, char ***split_line, char ***rgb)
{
	if (!is_color_identifier(line))
		return (0);
	*split_line = ft_split(line, ' ');
	if (!*split_line || !(*split_line)[0] || !(*split_line)[1])
	{
		ft_free_split(*split_line);
		return (0);
	}
	*rgb = ft_split((*split_line)[1], ',');
	if (!*rgb || ft_arraylen(*rgb) != 3)
	{
		ft_free_split(*rgb);
		ft_free_split(*split_line);
		return (0);
	}
	return (1);
}

int	process_color_values(t_game *game, char **split_line, char **rgb)
{
	int	rgb_arr[3];

	if (!parse_and_validate_rgb_values(rgb, rgb_arr))
	{
		ft_free_split(rgb);
		ft_free_split(split_line);
		return (0);
	}
	return (finalize_color_processing(game, split_line, rgb, rgb_arr));
}

/*
** parse_color - Parses the color definition line.
** It validates the input line, splits it into components,
** and processes the RGB values.
** If the input is valid, it updates the game structure with the color values.
** If the input is invalid, it frees any allocated memory and returns 0.
**
** @param game: Pointer to the game structure.
** @param line: The input line containing the color definition.
** @return 1 if the color is parsed successfully, 0 otherwise.
*/
int	parse_color(t_game *game, char *line)
{
	char	**split_line;
	char	**rgb;
	int		result;

	split_line = NULL;
	rgb = NULL;
	if (!validate_color_input(line, &split_line, &rgb))
		return (0);
	result = process_color_values(game, split_line, rgb);
	return (result);
}
