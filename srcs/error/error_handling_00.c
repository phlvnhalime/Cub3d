/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling_00.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpehliva <hpehliva@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 14:20:43 by hpehliva          #+#    #+#             */
/*   Updated: 2025/07/16 10:21:22 by hpehliva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

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

/* Validation errors */

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
	ft_putstr_fd("\n", 2);
	exit(EXIT_FAILURE);
}

/* File errors */
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
