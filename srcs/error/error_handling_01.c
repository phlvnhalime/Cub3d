/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling_01.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julcalde <julcalde@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 14:39:56 by hpehliva          #+#    #+#             */
/*   Updated: 2025/07/23 00:53:20 by julcalde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

/*
** map_errors - Prints an error message to stderr and exits the program
** with a failure status.
** This function is called when a map validation fails.
** It prints a generic error message indicating that the map validation
** has failed, along with the coordinates (x, y) where the error occurred.
** If an additional error message is provided, it will be printed after
** the coordinates.
** The program then exits with EXIT_FAILURE.
**
** @param error_msg: A specific error message describing the issue.
** @param x: The x-coordinate where the error occurred (if applicable).
** @param y: The y-coordinate where the error occurred (if applicable).
** If x and y are both greater than 0, they will be printed in the format
** "(x, y)". If they are not applicable, they will not be printed.
** If error_msg is NULL, no specific error message will be printed.
** If error_msg is not NULL, it will be printed after the coordinates.
** If no coordinates are provided, only the generic error message will be
** printed.
*/
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

/*
** texture_error - Prints an error message to stderr and exits the program
** with a failure status.
** This function is called when a texture-related error occurs, such as
** when a texture file cannot be loaded or is invalid.
** It prints the texture name, path, and a specific error message if provided.
** If the texture name or path is not provided, it will not print that part
** of the message.
** The program then exits with EXIT_FAILURE.
**
** @param texture_name: The name of the texture that caused the error.
** @param path: The path to the texture file that caused the error.
** @param error_msg: A specific error message describing the issue.
** If NULL, no specific error message is printed.
*/
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

/*
** mlx_error - Prints an error message to stderr and exits the program
** with a failure status.
** This function is called when an MLX42 function fails.
** It prints a generic error message indicating that an MLX42 function
** has failed, along with the name of the function that caused the error.
** If the function name is not provided, it prints "Unknown function".
** The program then exits with EXIT_FAILURE.
**
** @param function_name: The name of the MLX42 function that failed.
*/
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

/*
** malloc_error - Prints an error message to stderr and exits the program
** with a failure status.
** This function is called when a memory allocation fails.
** It prints a generic error message indicating that memory allocation
** has failed, and then exits the program with EXIT_FAILURE.
*/
void	malloc_error(void)
{
	ft_putstr_fd("Error\n", 2);
	ft_putstr_fd("Memory allocation failed", 2);
	ft_putstr_fd("\n", 2);
	exit(EXIT_FAILURE);
}
