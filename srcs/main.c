/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julcalde <julcalde@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 11:49:13 by hpehliva          #+#    #+#             */
/*   Updated: 2025/07/22 20:03:07 by julcalde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	close_window(void *frame)
{
	t_game	*game;

	game = (t_game *)frame;
	garbco_game(game);
	mlx_close_window(game->mlx);
}

void	check_leaks(void)
{
	system("leaks ");
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
	game_loop(&game);
	garbco_game(&game);
	return (EXIT_SUCCESS);
}
