/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling_00.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julcalde <julcalde@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 14:20:43 by hpehliva          #+#    #+#             */
/*   Updated: 2025/07/23 00:52:27 by julcalde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

/*
** error_exit - Error handling function
** This function prints an error message to stderr and exits the program.
** It is used for general error handling where no specific game structure
** cleanup is needed.
** It exits the program with EXIT_FAILURE.
**
** @param msg: The error message to be printed. If NULL, no additional message
** is printed.
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
** error_exit_cleanup - Error handling with cleanup
** This function prints an error message to stderr, cleans up the game structure,
** and exits the program.
** It is used for error handling where the game structure needs to be cleaned up
** before exiting.
** It exits the program with EXIT_FAILURE.
**
** @param game: Pointer to the game structure that needs to be cleaned up.
** @param msg: The error message to be printed. If NULL, no additional message
** is printed.
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
** valid_error - Error handling for specifiers
** This function prints an error message to stderr
** when a specifier is invalid or not found.
** It can also include additional content before the specifier.
** It exits the program with EXIT_FAILURE.
**
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
** file_error - Error handling for file operations
** This function prints an error message to stderr
** when a file operation fails, such as opening or reading a file.
** It includes the filename and an optional error message.
** It exits the program with EXIT_FAILURE.
**
** @param filename: The name of the file that caused the error.
** @param error_msg: An optional error message to be printed.
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
