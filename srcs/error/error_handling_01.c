/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling_01.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julcalde <julcalde@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 14:39:56 by hpehliva          #+#    #+#             */
/*   Updated: 2025/07/13 13:32:45 by julcalde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

/* Map validation errors */
void	map_errors(char *error_msg, int x, int y)
{
	ft_putstr_fd("Error\n", 2);
	ft_putstr_fd("Map validation failed", 2);
	if (x > 0 && y > 0)
	{
		ft_putstr_fd(" at position: (", 2);
		ft_putnbr_fd(x, 2);
		ft_putstr_fd(", ", 2);
		ft_putnbr_fd(y, 2);
	}
	if (error_msg)
	{
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(error_msg, 2);
	}
	ft_putstr_fd("\n", 2);
	exit(EXIT_FAILURE);
}

/* Texture errors */
void	texture_error(char *texture_name, char *path, char *error_msg)
{
	ft_putstr_fd("Error\n", 2);
	if (texture_name)
	{
		ft_putstr_fd("Texture: '", 2);
		ft_putstr_fd(texture_name, 2);
		ft_putstr_fd("': ", 2);
	}
	if (path)
	{
		ft_putstr_fd("Path: '", 2);
		ft_putstr_fd(path, 2);
		ft_putstr_fd("': ", 2);
	}
	if (error_msg)
	{
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(error_msg, 2);
	}
	ft_putstr_fd("\n", 2);
	exit(EXIT_FAILURE);
}

/* mlx errors */
void	mlx_error(char *function_name)
{
	ft_putstr_fd("Error\n", 2);
	ft_putstr_fd("MLX: ", 2);
	if (function_name)
		ft_putstr_fd(function_name, 2);
	else
		ft_putstr_fd("Unknown function", 2);
	ft_putstr_fd("\n", 2);
	exit(EXIT_FAILURE);
}

void	malloc_error(void)
{
	ft_putstr_fd("Error\n", 2);
	ft_putstr_fd("Memory allocation failed", 2);
	ft_putstr_fd("\n", 2);
	exit(EXIT_FAILURE);
}
