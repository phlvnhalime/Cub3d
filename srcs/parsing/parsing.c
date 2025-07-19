/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julcalde <julcalde@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 20:35:21 by hpehliva          #+#    #+#             */
/*   Updated: 2025/07/19 11:23:00 by julcalde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	get_texture_count(char *line)
{
	if (!line)
		return (0);
	if (ft_strncmp(line, "NO ", 3) == 0)
		return (0);
	else if (ft_strncmp(line, "SO ", 3) == 0)
		return (1);
	else if (ft_strncmp(line, "WE ", 3) == 0)
		return (2);
	else if (ft_strncmp(line, "EA ", 3) == 0)
		return (3);
	return (-1);
}

int	valid_rgb_format(int r, int g, int b)
{
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
	{
		DEBUG_PRINT("Invalid RGB format: %d, %d, %d\n", r, g, b);
		return (0);
	}
	return (1);
}

void	set_color_values(t_game *game, char identifier, int rgb_arr[3])
{
	if (identifier == 'F')
	{
		game->floor_color.r = rgb_arr[0];
		game->floor_color.g = rgb_arr[1];
		game->floor_color.b = rgb_arr[2];
		game->floor_color.hex = (rgb_arr[0] << 16) | (rgb_arr[1] << 8) \
		| rgb_arr[2];
	}
	else if (identifier == 'C')
	{
		game->ceiling_color.r = rgb_arr[0];
		game->ceiling_color.g = rgb_arr[1];
		game->ceiling_color.b = rgb_arr[2];
		game->ceiling_color.hex = (rgb_arr[0] << 16) | (rgb_arr[1] << 8) \
		| rgb_arr[2];
	}
	game->color_count++;
	DEBUG_PRINT(RD "Color set: %c %d,%d,%d\n" RST, identifier, rgb_arr[0],
		rgb_arr[1], rgb_arr[2]);
	DEBUG_PRINT(RD "Color hex: %x\n" RST,
		(rgb_arr[0] << 16) | (rgb_arr[1] << 8) | rgb_arr[2]);
	DEBUG_PRINT(GRN "Check color from parsing part is done.\n" RST);
}

int	parse_color(t_game *game, char *line)
{
	char	**split_line;
	char	**rgb;
	int		rgb_arr[3];

	if (!is_color_identifier(line))
	{
		DEBUG_PRINT("Invalid color identifier: %s\n", line);
		return (0);
	}
	split_line = ft_split(line, ' ');
	if (!split_line || !split_line[0] || !split_line[1])
	{
		DEBUG_PRINT("Invalid color format: %s\n", line);
		ft_free_split(split_line);
		return (0);
	}
	rgb = ft_split(split_line[1], ',');
	if (!rgb || ft_arraylen(rgb) != 3)
	{
		DEBUG_PRINT("Invalid RGB format: %s\n", split_line[1]);
		ft_free_split(rgb);
		ft_free_split(split_line);
		return (0);
	}
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

int	parse_file(t_game *game, char *file)
{
	int	fd;

	fd = open_and_validate_file(file);
	if (fd < 0)
		return (0);
	if (!parse_textures_and_colors(game, fd))
	{
		close(fd);
		error_exit_cleanup(game, "Failed to parse textures and colors");
	}
	if (!parse_map_section(game, fd))
	{
		close(fd);
		error_exit_cleanup(game, "Failed to parse map section");
	}
	close(fd);
	valid_map(game);
	if (!game->map_valid)
		error_exit_cleanup(game, "Map validation failed");
	DEBUG_PRINT(GRN "File parsing completed successfully\n" RST);
	return (1);
}
