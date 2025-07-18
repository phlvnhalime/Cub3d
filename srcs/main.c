/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpehliva <hpehliva@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 11:49:13 by hpehliva          #+#    #+#             */
/*   Updated: 2025/07/16 12:28:28 by hpehliva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	close_window(void *frame)
{
	t_game	*game;

	game = (t_game *)frame;
	DEBUG_PRINT(YLW "Window close required\n" RST);
	garbco_game(game);
	mlx_close_window(game->mlx);
}

void	check_leaks(void)
{
	system("leaks cub3D");
}

int	main(int ac, char **av)
{
	t_game	game;

	if (!validate_args(ac, av))
	{
		garbco_clean(&game.garbco);
		return (EXIT_FAILURE);
	}
	init_game(&game);
	if (!parse_file(&game, av[1]))
	{
		garbco_clean(&game.garbco);
		return (EXIT_FAILURE);
	}
	atexit(check_leaks);
	DEBUG_PRINT(GRN "Starting game loop... \n" RST);
	game_loop(&game);
	garbco_game(&game);
	return (EXIT_SUCCESS);
}
