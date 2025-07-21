/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpehliva <hpehliva@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 14:01:21 by hpehliva          #+#    #+#             */
/*   Updated: 2025/07/21 15:47:10 by hpehliva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	valid_rgb_format(int r, int g, int b)
{
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		return (0);
	return (1);
}

void	set_color_values(t_game *game, char identifier, int rgb_arr[3])
{
	if (identifier == 'F')
	{
		game->floor_color.r = rgb_arr[0];
		game->floor_color.g = rgb_arr[1];
		game->floor_color.b = rgb_arr[2];
		game->floor_color.hex = (rgb_arr[0] << 16) |
		 			(rgb_arr[1] << 8) | rgb_arr[2];
	}
	else if (identifier == 'C')
	{
		game->ceiling_color.r = rgb_arr[0];
		game->ceiling_color.g = rgb_arr[1];
		game->ceiling_color.b = rgb_arr[2];
		game->ceiling_color.hex = (rgb_arr[0] << 16) | 
					(rgb_arr[1] << 8) | rgb_arr[2];
	}
	game->color_count++;
}

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