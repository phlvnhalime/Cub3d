/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validations.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpehliva <hpehliva@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 14:43:33 by hpehliva          #+#    #+#             */
/*   Updated: 2025/07/21 16:33:22 by hpehliva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

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
