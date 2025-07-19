/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_texture.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julcalde <julcalde@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 10:58:28 by julcalde          #+#    #+#             */
/*   Updated: 2025/07/19 11:02:53 by julcalde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"
// ORIGINAL PARSE_TEXTURE FUNCTION

// int	parse_texture(t_game *game, char *line)
// {
// 	char	*path;
// 	int		i;

// 	i = get_texture_count(line);
// 	if (i == -1)
// 	{
// 		DEBUG_PRINT("Invalid texture identifier: %s\n", line);
// 		return (0);
// 	}
// 	path = ft_strtrim(line + 3, " \t\n");
// 	if (!path || ft_strlen(path) == 0)
// 	{
// 		DEBUG_PRINT("Invalid texture path: %s\n", line);
// 		free(line);
// 		garbco_add(&game->garbco, path);
// 		return (0);
// 	}
// 	if (game->textures[i].texture != NULL)
// 	{
// 		DEBUG_PRINT("Texture already loaded: %s\n", path);
// 		garbco_delete_txtr(game);
// 		return (0);
// 	}
// 	DEBUG_PRINT(CYN "Attempting to load texture: %s\n" RST, path);
// 	game->textures[i].texture = mlx_load_png(path);
// 	if (!game->textures[i].texture)
// 	{
// 		DEBUG_PRINT("Failed to load texture: %s\n", path);
// 		garbco_delete_txtr(game);
// 		return (0);
// 	}
// 	DEBUG_PRINT(GRN "Texture loaded successfully: %s\n" RST, path);
// 	garbco_add(&game->garbco, path);
// 	game->textures[i].path = path;
// 	game->texture_count++;
// 	DEBUG_PRINT(RD "Texture loaded: %s\n" RST, path);
// 	DEBUG_PRINT(RD "Texture count: %d\n" RST, game->texture_count);
// 	return (1);
// }

static int	validate_texture_input(t_game *game, char *line, \
		int *i, char **path)
{
	*i = get_texture_count(line);
	if (*i == -1)
	{
		DEBUG_PRINT("Invalid texture identifier: %s\n", line);
		return (0);
	}
	*path = ft_strtrim(line + 3, " \t\n");
	if (!*path || ft_strlen(*path) == 0)
	{
		DEBUG_PRINT("Invalid texture path: %s\n", line);
		free(line);
		garbco_add(&game->garbco, *path);
		return (0);
	}
	if (game->textures[*i].texture != NULL)
	{
		DEBUG_PRINT("Texture already loaded: %s\n", *path);
		garbco_delete_txtr(game);
		return (0);
	}
	return (1);
}

static int	load_texture(t_game *game, char *path, int i)
{
	DEBUG_PRINT(CYN "Attempting to load texture: %s\n" RST, path);
	game->textures[i].texture = mlx_load_png(path);
	if (!game->textures[i].texture)
	{
		DEBUG_PRINT("Failed to load texture: %s\n", path);
		garbco_delete_txtr(game);
		return (0);
	}
	DEBUG_PRINT(GRN "Texture loaded successfully: %s\n" RST, path);
	garbco_add(&game->garbco, path);
	game->textures[i].path = path;
	game->texture_count++;
	DEBUG_PRINT(RD "Texture loaded: %s\n" RST, path);
	DEBUG_PRINT(RD "Texture count: %d\n" RST, game->texture_count);
	return (1);
}

int	parse_texture(t_game *game, char *line)
{
	int		i;
	char	*path;

	if (!validate_texture_input(game, line, &i, &path))
		return (0);
	return (load_texture(game, path, i));
}
