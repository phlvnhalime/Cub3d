/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils01_parsing.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julcalde <julcalde@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 20:44:45 by hpehliva          #+#    #+#             */
/*   Updated: 2025/07/22 23:52:53 by julcalde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

/*
** ft_free_split - Frees a 2D array of strings.
** This function iterates through the array, freeing each string,
** and then frees the array itself. It checks if the array is NULL before
** attempting to free it to avoid dereferencing a NULL pointer.
**
** @param split The 2D array of strings to be freed.
*/
void	ft_free_split(char **split)
{
	int	i;

	if (!split)
		return ;
	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

/*
** print_texture_error - Prints an error message for texture loading issues.
** This function formats the error message with the texture name and
** additional information if provided. It then exits the program with a failure
** status.
**
** @param texture_name The name of the texture (e.g., "NO", "SO", "WE", "EA").
** @param message The error message to display.
** @param path The file path of the texture, if available.
*/
void	print_texture_error(char *texture_name, char *message, char *path)
{
	ft_putstr_fd("Error\n", 2);
	ft_putstr_fd(texture_name, 2);
	ft_putstr_fd(" texture: ", 2);
	ft_putstr_fd(message, 2);
	if (path)
	{
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(path, 2);
	}
	ft_putstr_fd("\n", 2);
	exit(EXIT_FAILURE);
}

/*
** extract_texture_path - Extracts the texture path from a line.
** This function trims the line to get the texture path, ensuring it starts
** with the texture identifier (e.g., "NO ", "SO ", "WE ", "EA ").
**
** @param line The line containing the texture definition.
** @param texture_name The name of the texture for error reporting.
** @return Returns the trimmed path if valid, otherwise prints an error and
** returns NULL.
*/
char	*extract_texture_path(char *line, char *texture_name)
{
	char	*path;

	path = ft_strtrim(line + 3, " \t\n");
	if (!path || ft_strlen(path) == 0)
	{
		print_texture_error(texture_name, "missing path", NULL);
		if (path)
			free(path);
		return (NULL);
	}
	return (path);
}

/*
** validate_texture_path - Validates the texture file path.
** This function checks if the provided texture path ends with ".png"
** and if the file exists. If the validation fails, it prints an error message.
**
** @param path The file path to the texture.
** @param texture_name The name of the texture for error reporting.
** @return Returns 1 if the path is valid, otherwise returns 0.
*/
int	validate_texture_path(char *path, char *texture_name)
{
	size_t	path_len;

	path_len = ft_strlen(path);
	if (path_len < 4 || ft_strncmp(path + path_len - 4, ".png", 4) != 0)
	{
		print_texture_error(texture_name, "file extension must be '.png'",
			path);
		return (0);
	}
	if (!file_exists(path))
	{
		print_texture_error(texture_name, "file not found", path);
		return (0);
	}
	return (1);
}

/*
** load_texture - Loads a texture from a PNG file.
** This function attempts to load a texture from the specified file path.
** If the texture fails to load, it prints an error message and returns NULL.
**
** @param path The file path to the texture.
** @param texture_name The name of the texture for error reporting.
*/
void	*load_texture(char *path, char *texture_name)
{
	void	*texture;

	texture = mlx_load_png(path);
	if (!texture)
	{
		print_texture_error(texture_name, "failed to load texture", path);
		return (NULL);
	}
	return (texture);
}
