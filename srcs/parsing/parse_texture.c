/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_texture.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpehliva <hpehliva@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 14:01:40 by hpehliva          #+#    #+#             */
/*   Updated: 2025/07/21 14:38:33 by hpehliva         ###   ########.fr       */
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

int	parse_texture(t_game *game, char *line)
{
	char	*path;
	int		i;
	size_t	path_len;

	i = get_texture_count(line);
	if (i == -1)
		return (0);
	path = ft_strtrim(line + 3, " \t\n");
	if (!path || ft_strlen(path) == 0)
		return (0);
	path_len = ft_strlen(path);
	if (path_len < 4 || ft_strncmp(path + path_len - 4, ".png", 4) != 0)
	{
		garbco_add(&game->garbco, (char *)path);
		return (0);
	}
	if (game->textures[i].texture != NULL)
	{
		garbco_delete_txtr(game);
		return (0);
	}
	game->textures[i].texture = mlx_load_png(path);
	if (!game->textures[i].texture)
	{
		garbco_delete_txtr(game);
		garbco_add(&game->garbco, (char *)path);
		return (0);
	}
	garbco_add(&game->garbco, (char *)path);
	game->textures[i].path = (char *)path;
	game->texture_count++;
	return (1);
}
