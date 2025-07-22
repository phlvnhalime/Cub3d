/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_texture.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julcalde <julcalde@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 14:01:40 by hpehliva          #+#    #+#             */
/*   Updated: 2025/07/22 23:09:30 by julcalde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

/*
** get_texture_count - Determines the index of the texture based on the line
** content.
** This function checks the beginning of the line to identify which texture
** it corresponds to (NO, SO, WE, EA). It returns an index that can be used
** to access the appropriate texture in the game structure.
**
** @param line The line from the configuration file.
** @return The index of the texture (0 for NO, 1 for SO, 2 for WE, 3 for EA),
*/
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

/*
** get_texture_name - Returns the name of the texture based on its index.
** This function maps the texture index to its corresponding name.
** It is used to provide a human-readable name for error messages and
** debugging purposes.
**
** @param index The index of the texture (0 for NO, 1 for SO, etc.).
** @return The name of the texture as a string.
*/
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

/*
** file_exists - Checks if a file exists at the given path.
** This function attempts to open the file in read-only mode. If the file
** can be opened, it is considered to exist, and the function returns 1.
** If the file cannot be opened (e.g., it does not exist), the function
** returns 0.
**
** @param path The path to the file to check.
** @return 1 if the file exists, 0 if it does not.
*/
int	file_exists(char *path)
{
	int	fd;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (0);
	close(fd);
	return (1);
}

/*
** parse_texture - Parses a texture line from the configuration file.
** This function extracts the texture path from the line, validates it,
** and loads the texture into the game structure.
** It also checks if the texture has already been set and handles errors
** accordingly.
**
** @param game Pointer to the game structure.
** @param line The line from the configuration file containing the texture
** information.
** @return 1 on success, 0 on failure.
*/
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
