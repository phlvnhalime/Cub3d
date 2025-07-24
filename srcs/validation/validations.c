/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validations.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julcalde <julcalde@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 14:43:33 by hpehliva          #+#    #+#             */
/*   Updated: 2025/07/23 00:17:57 by julcalde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

/*
** validate_args - Validates the command line arguments.
** This function checks if the number of arguments is correct and if the
** map file has the correct extension (.cub).
**
** @param ac - The number of command line arguments.
** @param av - The array of command line arguments.
*/
int	validate_args(int ac, char **av)
{
	int	len;

	if (ac != 2)
	{
		printf("Usage: %s <map_name.cub>\n", av[0]);
		return (0);
	}
	len = strlen(av[1]);
	if (len < 5 || strcmp(av[1] + len - 4, ".cub") != 0)
	{
		printf("Error: Map file must have '.cub' extension\n");
		return (0);
	}
	return (1);
}

/*
** valid_map - Validates the map structure.
** This function checks if the map has a valid height and width,
** if a player position is found, and if the map is surrounded by walls.
** If any of these checks fail, it sets the map_valid flag to 0.
**
** @param game - Pointer to the game structure containing the map data.
*/
void	valid_map(t_game *game)
{
	if (game->map.height < 3 || game->map.width < 3)
	{
		game->map_valid = 0;
		return ;
	}
	if (!find_player_position(game))
	{
		game->map_valid = 0;
		return ;
	}
	if (!check_map_walls(game))
	{
		game->map_valid = 0;
		return ;
	}
	game->map_valid = 1;
}

/*
** open_and_validate_file - Opens and validates the map file.
** This function attempts to open the specified file in read-only mode.
** If the file cannot be opened, it calls file_error to handle the error.
**
** @param file_path - The path to the map file to be opened.
** @return - Returns the file descriptor if successful, or
	-1 if an error occurs.
*/
int	open_and_validate_file(char *file_path)
{
	int	fd;

	fd = open(file_path, O_RDONLY);
	if (fd < 0)
	{
		file_error(file_path, "Cannot open file");
		return (-1);
	}
	return (fd);
}
