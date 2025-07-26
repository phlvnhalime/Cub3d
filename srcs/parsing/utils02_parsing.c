/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils02_parsing.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julcalde <julcalde@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 21:39:13 by hpehliva          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2025/07/26 11:30:54 by julcalde         ###   ########.fr       */
=======
/*   Updated: 2025/07/26 11:38:58 by hpehliva         ###   ########.fr       */
>>>>>>> 758cd9545487d1f62121489195d99d27aa3267e3
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

/*
** is_digit - Checks if a string contains only digits.
** This function checks if the string contains only digits (0-9).
** It ignores leading spaces and tabs and returns 0 if the string is empty.
**
** @param str: The string to check.
** @return 1 if the string contains only digits, 0 otherwise.
*/

int	is_digit(char *str)
{
	int	i;
	int	len;

	i = 0;
	if (!str)
		return (0);
	while (str[i] == ' ' || str[i] == '\t' || str[i] == ',')
		i++;
	if (!str[i])
		return (0);
	len = ft_strlen(str);
	while (len > i && (str[len - 1] == ' ' || str[len - 1] == '\t'))
		len--;
	while (i < len)
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

int	parse_and_validate_rgb_values(char **rgb, int rgb_arr[3])
{
	int	i;
	int	len;

	if (!rgb)
		return (0);
	i = 0;
	while (i < 3)
	{
		if (!rgb[i])
			return (0);
		len = ft_strlen(rgb[i]);
		if ((len > 0 && rgb[i][len - 1] == '\n') || (rgb[i][len - 1] == ' '
				|| rgb[i][len - 1] == '\t' || rgb[i][len - 1] == ','))
			rgb[i][len - 1] = '\0';
		i++;
	}
	if (!is_digit(rgb[0]) || !is_digit(rgb[1]) || !is_digit(rgb[2]))
		return (valid_error("Invalid RGB values",
				"rgb values are missing or non digit\n"), 0);
	rgb_arr[0] = ft_atoi(rgb[0]);
	rgb_arr[1] = ft_atoi(rgb[1]);
	rgb_arr[2] = ft_atoi(rgb[2]);
	return (1);
}

/*
** finalize_color_processing - Finalizes the color processing.
** This function validates the RGB values and
** sets the color values in the game structure.
** It frees the allocated memory for the split line and RGB values.
**
** @param game: Pointer to the game structure.
*/

int	finalize_color_processing(t_game *game, char **split_line, char **rgb,
		int rgb_arr[3])
{
	if (!valid_rgb_format(rgb_arr[0], rgb_arr[1], rgb_arr[2]))
	{
		ft_free_split(rgb);
		ft_free_split(split_line);
		return (0);
	}
	set_color_values(game, split_line[0][0], rgb_arr);
	ft_free_split(rgb);
	ft_free_split(split_line);
	return (1);
}
