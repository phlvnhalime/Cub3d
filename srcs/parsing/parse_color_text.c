/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_color_text.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpehliva <hpehliva@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 14:01:08 by hpehliva          #+#    #+#             */
/*   Updated: 2025/07/21 15:39:59 by hpehliva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static int	handle_texture(t_game *game, char *line, int *nbr_element)
{
	if (parse_texture(game, line))
	{
		(*nbr_element)++;
		return (1);
	}
	free(line);
	return (0);
}

static int	handle_color(t_game *game, char *line, int *nbr_element)
{
	if (parse_color(game, line))
	{
		(*nbr_element)++;
		return (1);
	}
	free(line);
	return (0);
}

static int	process_element(t_game *game, char *line, int *nbr_element)
{
	if (texture_identifier(line))
		return (handle_texture(game, line, nbr_element));
	if (is_color_identifier(line))
		return (handle_color(game, line, nbr_element));
	valid_error("Invalid line in texture or color section", line);
	return (0);
}

int	parse_textures_and_colors(t_game *game, int fd)
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
		if (!process_element(game, line, &nbr_element))
		{
			free(line);
			return (0);
		}
		free(line);
	}
	return (nbr_element == 6);
}
