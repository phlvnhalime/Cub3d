/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_00.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpehliva <hpehliva@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 15:50:30 by hpehliva          #+#    #+#             */
/*   Updated: 2025/07/12 15:57:39 by hpehliva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int parse_map_section(t_game *game, int fd)
{
    char *line;

    game->map_started = 1;
    while ((line = get_next_line(fd)))
    {
        if (!is_empty_line(line) && is_map_line(line))
        {
            if (!parse_map_line(game, line))
            {
                free(line);
                return (0);
            }
        }
        else if (!is_empty_line(line))
        {
            free(line);
            valid_error("Invalid line in map section", line);
        }
        free(line);
    }

    if (game->map.height == 0)
        return (0);
    
    return (1);
}
