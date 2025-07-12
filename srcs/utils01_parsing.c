/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils01_parsing.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julcalde <julcalde@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 20:44:45 by hpehliva          #+#    #+#             */
/*   Updated: 2025/07/12 14:54:39 by julcalde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

/*
	Frees a 2D array of strings (split).
	- split: The 2D array to free
	Iterates through each string in the array, frees it, and then frees the 
	array itself.
	Assumes that split is NULL-terminated.
*/
void	ft_free_split(char **split)
{
	int	i;

	if (!split)
		return ;
	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

/*
	Validates the command line arguments.
	- ac: Argument count
	- av: Argument vector
	Returns 1 if valid, 0 otherwise.
	Checks if exactly one argument is provided and if it ends with ".cub".
	If not valid, prints usage instructions or error message.
*/
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

/*
	Prints an error message and exits the program.
	- msg: The error message to print
	Exits with EXIT_FAILURE.
*/
void	error_exit(char *msg)
{
	fprintf(stderr, "Error\n %s\n", msg);
	exit(EXIT_FAILURE);
}

/*
	Renders a frame by calling the raycasting function.
	- frame: Pointer to the game structure containing game state
	Assumes that the frame is of type t_game.
*/
void	render_frame(void *frame)
{
	t_game	*game;

	game = (t_game *)frame;
	raycast(game);
	DEBUG_PRINT(GRN"Frame rendered\n"RST);
}

/*
	Closes the window and cleans up resources.
	- frame: Pointer to the game structure containing game state
	Assumes that the frame is of type t_game.
	Prints a debug message indicating that the window close was requested.
*/
void	close_window(void *frame)
{
	t_game	*game;

	game = (t_game *)frame;
	DEBUG_PRINT(YLW"Window close required\n"RST);
	mlx_close_window(game->mlx);
}
