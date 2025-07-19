/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julcalde <julcalde@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 11:25:03 by julcalde          #+#    #+#             */
/*   Updated: 2025/07/19 11:28:51 by julcalde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

// ORIGINAL VERSION of parse_color function

// int	parse_color(t_game *game, char *line)
// {
// 	char	**split_line;
// 	char	**rgb;
// 	int		rgb_arr[3];

// 	if (!is_color_identifier(line))
// 	{
// 		DEBUG_PRINT("Invalid color identifier: %s\n", line);
// 		return (0);
// 	}
// 	split_line = ft_split(line, ' ');
// 	if (!split_line || !split_line[0] || !split_line[1])
// 	{
// 		DEBUG_PRINT("Invalid color format: %s\n", line);
// 		ft_free_split(split_line);
// 		return (0);
// 	}
// 	rgb = ft_split(split_line[1], ',');
// 	if (!rgb || ft_arraylen(rgb) != 3)
// 	{
// 		DEBUG_PRINT("Invalid RGB format: %s\n", split_line[1]);
// 		ft_free_split(rgb);
// 		ft_free_split(split_line);
// 		return (0);
// 	}
// 	rgb_arr[0] = ft_atoi(rgb[0]);
// 	rgb_arr[1] = ft_atoi(rgb[1]);
// 	rgb_arr[2] = ft_atoi(rgb[2]);
// 	if (!valid_rgb_format(rgb_arr[0], rgb_arr[1], rgb_arr[2]))
// 	{
// 		ft_free_split(rgb);
// 		ft_free_split(split_line);
// 		return (0);
// 	}
// 	set_color_values(game, split_line[0][0], rgb_arr);
// 	ft_free_split(rgb);
// 	ft_free_split(split_line);
// 	return (1);
// }

static int	validate_color_input(char *line, char ***split_line, char ***rgb)
{
	if (!is_color_identifier(line))
	{
		DEBUG_PRINT("Invalid color identifier: %s\n", line);
		return (0);
	}
	*split_line = ft_split(line, ' ');
	if (!*split_line || !(*split_line)[0] || !(*split_line)[1])
	{
		DEBUG_PRINT("Invalid color format: %s\n", line);
		ft_free_split(*split_line);
		return (0);
	}
	*rgb = ft_split((*split_line)[1], ',');
	if (!*rgb || ft_arraylen(*rgb) != 3)
	{
		DEBUG_PRINT("Invalid RGB format: %s\n", (*split_line)[1]);
		ft_free_split(*rgb);
		ft_free_split(*split_line);
		return (0);
	}
	return (1);
}

static int	process_color_values(t_game *game, char **split_line, char **rgb)
{
	int	rgb_arr[3];

	rgb_arr[0] = ft_atoi(rgb[0]);
	rgb_arr[1] = ft_atoi(rgb[1]);
	rgb_arr[2] = ft_atoi(rgb[2]);
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

int	parse_color(t_game *game, char *line)
{
	char	**split_line;
	char	**rgb;

	if (!validate_color_input(line, &split_line, &rgb))
		return (0);
	return (process_color_values(game, split_line, rgb));
}
