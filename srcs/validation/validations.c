/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validations.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpehliva <hpehliva@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 14:43:33 by hpehliva          #+#    #+#             */
/*   Updated: 2025/07/12 15:51:16 by hpehliva         ###   ########.fr       */
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

void valid_map(t_game *game)
{
    if (game->map.height < 3 || game->map.width < 3)
    {
        DEBUG_PRINT(RD"Map is too small (width: %d, height: %d)\n"RST, game->map.width, game->map.height);
        game->map_valid = 0;
        return;
    }
    if (!find_player_position(game))
    {
        DEBUG_PRINT(RD"Player position not found or invalid\n"RST);
        game->map_valid = 0;
        return;
    }
    if (!check_map_walls(game))
    {
        DEBUG_PRINT(RD"Map walls are not valid\n"RST);
        game->map_valid = 0;
        return;
    }
    game->map_valid = 1;
    DEBUG_PRINT(GRN"Map is valid\n"RST);
}

int open_and_validate_file(char *file_path)
{
    int fd = open(file_path, O_RDONLY);
    if (fd < 0)
    {
        file_error(file_path, "Cannot open file");
        return (-1);
    }
    return (fd);
}
