/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_color_text.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpehliva <hpehliva@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 14:01:08 by hpehliva          #+#    #+#             */
/*   Updated: 2025/07/23 16:17:19 by hpehliva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

/*
** handle_texture - Handles the texture definition line.
** It calls the parse_texture function to validate and store the texture.
** Returns 1 if the texture is parsed successfully, 0 otherwise.
**
** @param game: Pointer to the game structure.
** @param line: The line containing the texture definition.
** @param nbr_element: Pointer to the count of processed elements.
** @return 1 if the texture is parsed successfully, 0 otherwise.
*/
static int	handle_texture(t_game *game, char *line, int *nbr_element)
{
	if (parse_texture(game, line))
	{
		(*nbr_element)++;
		return (1);
	}
	// free(line);
	return (0);
}

/*
** handle_color - Handles the color definition line.
** It calls the parse_color function to validate and store the color.
** Returns 1 if the color is parsed successfully, 0 otherwise.
**
** @param game: Pointer to the game structure.
** @param line: The line containing the color definition.
** @param nbr_element: Pointer to the count of processed elements.
** @return 1 if the color is parsed successfully, 0 otherwise.
*/
static int	handle_color(t_game *game, char *line, int *nbr_element)
{
	if (parse_color(game, line))
	{
		(*nbr_element)++;
		return (1);
	}
	// free(line);
	return (0);
}

/*
** process_element - Processes a single line to determine if it is a
** texture or color definition.
** It calls the appropriate handler function based on the line content.
** Returns 1 if the line is processed successfully, 0 otherwise.
**
** @param game: Pointer to the game structure.
** @param line: The line to process.
** @param nbr_element: Pointer to the count of processed elements.
** @return 1 if the line is processed successfully, 0 otherwise.
*/
static int	process_element(t_game *game, char *line, int *nbr_element)
{
	if (texture_identifier(line))
		return (handle_texture(game, line, nbr_element));
	if (is_color_identifier(line))
		return (handle_color(game, line, nbr_element));
	valid_error("Invalid line in texture or color section", line);
	return (0);
}

/*
** parse_textures_and_colors - Parses the texture and color definitions
** from the provided file descriptor.
** It reads lines until it finds all required elements (6 in total).
** Returns 1 if all elements are found, 0 otherwise.
**
** @param game: Pointer to the game structure.
** @param fd: File descriptor to read from.
** @return 1 if all elements are found, 0 otherwise.
*/
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
