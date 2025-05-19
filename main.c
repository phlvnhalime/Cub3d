/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julcalde <julcalde@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 13:59:46 by julcalde          #+#    #+#             */
/*   Updated: 2025/05/19 14:01:19 by julcalde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int argc, char **argv)
{
	if (argc != 2)
	{
		printf(RED "Error\n" RESET);
		printf("Usage: %s <cub_file>\n", argv[0]);
		return (EXIT_FAILURE);
	}
	return (0);
}
