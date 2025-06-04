/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julcalde <julcalde@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 00:47:46 by julcalde          #+#    #+#             */
/*   Updated: 2025/06/05 00:56:23 by julcalde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	parse_file(char *filename, t_game *game)
{
	int		i;
	int		fd;
	char	*line;
	char	**lines;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (0);
	lines = NULL;
	i = 0;
	while (i++)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		lines = realloc_lines(lines, line, i); // Function to reallocate lines array
	}
	close(fd);
	if (!process_lines(line, game)) // Function to process the lines read from the file
		return (0);
	free_lines(lines); // Function to free the lines array
	return (1);
}
