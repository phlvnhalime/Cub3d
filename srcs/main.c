/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpehliva <hpehliva@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 11:49:13 by hpehliva          #+#    #+#             */
/*   Updated: 2025/07/12 14:43:56 by hpehliva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"


void	render_frame(void *frame)
{
	t_game *game = (t_game *)frame;
	// Clean the screen for black background
	// memset(game->img->pixels... )
	raycast(game);
	DEBUG_PRINT(GRN"Frame rendered\n"RST);
}
void	close_window(void *frame)
{
	t_game *game = (t_game *)frame;
	DEBUG_PRINT(YLW"Window close required\n"RST); 
	mlx_close_window(game->mlx);
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

	if(nbr_element != 6)
	{
		close(fd);
		DEBUG_PRINT(RD"Missig textures or colors. Found %d/6\n"RST, nbr_element);
		return 0;
	}
	// Map parsing
	game->map_started = 1;
	while((line = get_next_line(fd)))
	{
		if(!is_empty_line(line) && is_map_line(line))
		{
			if(!parse_map_line(game, line))
			{
				free(line);
				close(fd);
				DEBUG_PRINT(RD"Failed to map parsing"RST);
				return 0;
			}
		}
		else if(!is_empty_line(line))
		{
			DEBUG_PRINT(RD"Invalid line in map section: %s\n"RST, line);
			free(line);
			close(fd);
			return 0;
		}
		free(line);
	}

	close(fd);
	//Map validation
	if(game->map.height == 0)
	{
		DEBUG_PRINT(RD"No map foud in the file"RST);
		return 0;
	}
	valid_map(game);
	if(!game->map_valid)
	{
		DEBUG_PRINT(RD"MAp validation failed"RST);
		return 0;
	}

	DEBUG_PRINT(GRN"File parsing completed successfully\n"RST);
	return (1); // Return true if all elements are parsed
}



int	main(int ac, char **av)
{
	t_game game;

	// If is it successful, we can now initialize the game window
	init_game(&game);
	if (!validate_args(ac, av))
		return (EXIT_FAILURE);

	garbco_init(&game.garbco);


	/*Parse arguments and set up game*/
	if (!parse_file(&game, av[1]))
	{
		garbco_game(&game);
		error_exit("Failed to parse .cub file");
	}


	DEBUG_PRINT(GRN"Starting game loop... \n"RST);
	game_loop(&game);
	garbco_game(&game);
	return (EXIT_SUCCESS);
}

