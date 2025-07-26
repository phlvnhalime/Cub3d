/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpehliva <hpehliva@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 11:49:13 by hpehliva          #+#    #+#             */
/*   Updated: 2025/07/26 11:33:15 by hpehliva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

/*
** close_window - Closes the game window and cleans up resources.
** This function is called when the window is closed by the user.
** It cleans up the game resources and closes the window using the mlx library.
**
** @param frame - Pointer to the game structure containing all necessary data.
*/
void	close_window(void *frame)
{
	t_game	*game;

	game = (t_game *)frame;
	mlx_close_window(game->mlx);
	garbco_game(game);
}

/*
** main - Entry point of the Cub3D game.
** This function initializes the game, validates the command line arguments,
** parses the map file, and starts the game loop.
** It also sets up a cleanup function to be called at exit to check for memory
** leaks.
**
** @param ac - The number of command line arguments.
** @param av - The array of command line arguments.
** @return EXIT_SUCCESS if the game runs successfully, EXIT_FAILURE otherwise.
*/
int	main(int ac, char **av)
{
	t_game	game;

	if (!validate_args(ac, av))
	{
		garbco_clean(&game.garbco);
		error_exit("Invalid input");
	}
	init_game(&game);
	if (!parse_file(&game, av[1]))
	{
		garbco_clean(&game.garbco);
		return (EXIT_FAILURE);
	}
	game_loop(&game);
	garbco_game(&game);
	return (EXIT_SUCCESS);
}
