/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_texture.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpehliva <hpehliva@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 14:01:40 by hpehliva          #+#    #+#             */
/*   Updated: 2025/07/21 16:41:29 by hpehliva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	get_texture_count(char *line)
{
	if (!line)
		return (-1);
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

char	*get_texture_name(int index)
{
	if (index == 0)
		return ("NO");
	else if (index == 1)
		return ("SO");
	else if (index == 2)
		return ("WE");
	else if (index == 3)
		return ("EA");
	else
		return ("unknown");
}

int	file_exists(char *path)
{
	int	fd;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (0);
	close(fd);
	return (1);
}

int	parse_texture(t_game *game, char *line)
{
	char	*path;
	int		i;
	char	*texture_name;

	i = get_texture_count(line);
	if (i == -1)
		return (0);
	texture_name = get_texture_name(i);
	if (game->textures[i].texture != NULL)
		return (print_texture_error(texture_name, "already set", NULL), 0);
	path = extract_texture_path(line, texture_name);
	if (!path)
		return (0);
	if (!validate_texture_path(path, texture_name))
		return (free(path), 0);
	game->textures[i].texture = load_texture(path, texture_name);
	if (!game->textures[i].texture)
		return (free(path), 0);
	garbco_add(&game->garbco, (char *)path);
	game->textures[i].path = (char *)path;
	game->texture_count++;
	return (1);
}
