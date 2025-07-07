/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpehliva <hpehliva@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 11:49:13 by hpehliva          #+#    #+#             */
/*   Updated: 2025/07/07 09:27:36 by hpehliva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	validate_args(int ac, char **av)
{
	int	len;

	if (ac != 2)
	{
		printf("Usage: %s <map_file.cub>\n", av[0]);
		return (0);
	}
	len = strlen(av[1]);
	if (len < 5 || strcmp(av[1] + len - 4, ".cub") != 0)
	{
		printf("Error: Map file must have '.cub' \n");
		return (0);
	}
	return (1);
}

void	error_exit(char *msg)
{
	fprintf(stderr, "Error\n %s\n", msg); // changed this func.
	exit(EXIT_FAILURE);
}

int	parse_file(t_game *game, char *file)
{
	int		fd;
	char	*line;
	int		nbr_element;

	nbr_element = 0;
	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (0);
	while ((line = get_next_line(fd)) && nbr_element < 6)
	{
		if(is_empty_line(line))
		{
			free(line);
			continue; // Skip empty lines
		}
		if (texture_identifier(line))
		{
			if (parse_texture(game, line))
			    nbr_element++;
		}
		else if(is_color_identifier(line))
		{
			if (parse_color(game, line))
                nbr_element++;
		}
		free(line);
	}
	//TODO: Add map parsing here
	/*
		1. Map lines detection
		2. Player position finding (N,S,E,W)
		3. Map validation (walls around)
		4. Grid structure creation
	*/
	close(fd);
	return (nbr_element == 6); // Return true if all elements are parsed
}
/*Start again*/

int	main(int ac, char **av)
{
	t_game game;
	if (!validate_args(ac, av))
		return (EXIT_FAILURE);

	/*TODO*/
    init_data(&game); // Initialized data structure

	/*Parse arguments and set up game*/
	if (!parse_file(&game, av[1]))
	{
		error_exit("Failed to parse .cub file");
	}

	// If is it successful, we can now initialize the game window
	init_game(&game);
}

