/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julcalde <julcalde@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 11:49:13 by hpehliva          #+#    #+#             */
/*   Updated: 2025/07/12 15:47:04 by julcalde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static int	parse_elements(t_game *game, int fd)
{
	char	*line;
	int		nbr_element;

	nbr_element = 0;
	while (nbr_element < 6)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		if (is_empty_line(line))
		{
			free(line);
			continue ;
		}
		if (texture_identifier(line) && parse_texture(game, line))
			nbr_element++;
		else if (is_color_identifier(line) && parse_color(game, line))
			nbr_element++;
		free(line);
	}
	if (nbr_element != 6)
		DEBUG_PRINT(RD"Missing textures or colors. Found %d/6\n"RST, \
			nbr_element);
	return (nbr_element == 6);
}

// static int	parse_map_section(t_game *game, int fd)
// {
// 	char	*line;

// 	while (1)
// 	{
// 		line = get_next_line(fd);
// 		if (!line)
// 			break ;
// 		if (!is_empty_line(line) && is_map_line(line))
// 		{
// 			if (!parse_map_line(game, line))
// 			{
// 				free(line);
// 				DEBUG_PRINT(RD"Failed to map parsing"RST);
// 				return (0);
// 			}
// 		}
// 		else if (!is_empty_line(line))
// 		{
// 			DEBUG_PRINT(RD"Invalid line in map section: %s\n"RST, line);
// 			free(line);
// 			return (0);
// 		}
// 		free(line);
// 	}
// 	if (game->map.height == 0)
// 	{
// 		DEBUG_PRINT(RD"No map found in the file"RST);
// 		return (0);
// 	}
// 	return (1);
// }

/*
	* Parses the provided .cub file to extract game elements and map data.
	* It opens the file, reads the elements (textures and colors), and then
	* parses the map section.
	* If any parsing fails, it closes the file and returns 0. 
	* If successful, it validates the map and returns 1.
	@param game Pointer to the game structure.
	@param file Path to the .cub file.
	@return 1 if parsing is successful, 0 otherwise.
*/
int	parse_file(t_game *game, char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (0);
	if (!parse_elements(game, fd))
	{
		close(fd);
		return (0);
	}
	game->map_started = 1;
	if (!parse_map_section(game, fd))
	{
		close(fd);
		return (0);
	}
	close(fd);
	valid_map(game);
	if (!game->map_valid)
	{
		DEBUG_PRINT(RD"Map validation failed"RST);
		return (0);
	}
	DEBUG_PRINT(GRN"File parsing completed successfully\n"RST);
	return (1);
}

/*
	* Main function to initialize the game and start the game loop.
	* It validates the command line arguments, initializes the game structure,
	* and parses the provided .cub file. If parsing is successful, it enters the
	* game loop. If any errors occur during initialization or parsing,
	* it cleans up and exits with an error message.
	@param ac Argument count.
	@param av Argument vector containing the program name and the .cub file path.
	@return EXIT_SUCCESS if the game starts successfully, EXIT_FAILURE otherwise.
*/
int	main(int ac, char **av)
{
	t_game	game;

	init_game(&game);
	if (!validate_args(ac, av))
		return (EXIT_FAILURE);
	garbco_init(&game.garbco);
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
