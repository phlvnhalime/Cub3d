/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling_00.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julcalde <julcalde@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 14:20:43 by hpehliva          #+#    #+#             */
/*   Updated: 2025/07/22 20:21:13 by julcalde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

/*
** Error exit handling
** Prints the error message to stderr.
** Exits the program with EXIT_FAILURE.
*
** @param msg: The error message to be printed.
** If msg is NULL, only "Error" is printed.
*/
void	error_exit(char *msg)
{
	ft_putstr_fd("Error\n", 2);
	if (msg)
	{
		ft_putstr_fd(msg, 2);
		ft_putstr_fd("\n", 2);
	}
	exit(EXIT_FAILURE);
}

/*
** Error exit with cleanup
** Prints the error message to stderr.
** Cleans up the garbage collector if the game structure is provided.
** Exits the program with EXIT_FAILURE.
*
** @param game: Pointer to the game structure for cleanup.
** @param msg: The error message to be printed.
*/
void	error_exit_cleanup(t_game *game, char *msg)
{
	ft_putstr_fd("Error\n", 2);
	if (msg)
		ft_putstr_fd(msg, 2);
	ft_putstr_fd("\n", 2);
	if (game)
		garbco_clean(&game->garbco);
	exit(EXIT_FAILURE);
}

/*
** Validity error handling
** Prints the error message to stderr.
** If content is provided, it prints it before the specifier.
** Exits the program with EXIT_FAILURE.
*
** @param content: Additional content to be printed before the specifier.
** @param specifier: The specifier that caused the error.
*/
void	valid_error(char *content, char *specifier)
{
	ft_putstr_fd("Error\n", 2);
	if (content)
	{
		ft_putstr_fd(content, 2);
		ft_putstr_fd(": ", 2);
	}
	if (specifier)
		ft_putstr_fd(specifier, 2);
	exit(EXIT_FAILURE);
}

/*
** File error handling
** Prints the filename and the error message to stderr.
** Exits the program with EXIT_FAILURE.
*
** @param filename: The name of the file that caused the error.
** @param error_msg: The error message to be printed.
*/
void	file_error(char *filename, char *error_msg)
{
	ft_putstr_fd("Error\n", 2);
	ft_putstr_fd("File: '", 2);
	if (filename)
		ft_putstr_fd(filename, 2);
	ft_putstr_fd("': ", 2);
	if (error_msg)
		ft_putstr_fd(error_msg, 2);
	ft_putstr_fd("\n", 2);
	exit(EXIT_FAILURE);
}
