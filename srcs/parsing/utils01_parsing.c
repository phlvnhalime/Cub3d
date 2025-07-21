/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils01_parsing.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpehliva <hpehliva@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 20:44:45 by hpehliva          #+#    #+#             */
/*   Updated: 2025/07/21 15:48:56 by hpehliva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

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

int	validate_texture_path(char *path, char *texture_name)
{
	size_t	path_len;

	path_len = ft_strlen(path);
	if (path_len < 4 || ft_strncmp(path + path_len - 4, ".png", 4) != 0)
	{
		print_texture_error(texture_name, "invalid file extension", path);
		return (0);
	}
	if (!file_exists(path))
	{
		print_texture_error(texture_name, "file not found", path);
		return (0);
	}
	return (1);
}

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
