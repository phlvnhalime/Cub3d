/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julcalde <julcalde@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 11:49:13 by hpehliva          #+#    #+#             */
/*   Updated: 2025/07/13 14:38:09 by julcalde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	close_window(void *frame)
{
	t_game	*game;

	game = (t_game *)frame;
	DEBUG_PRINT(YLW"Window close required\n"RST);
	garbco_game(game);
	mlx_close_window(game->mlx);
}

int	main(int ac, char **av)
{
	t_game	game;

	if (!validate_args(ac, av))
		return (EXIT_FAILURE);
	init_game(&game);
	if (!parse_file(&game, av[1]))
	{
		return (EXIT_FAILURE);
	}
	DEBUG_PRINT(GRN"Starting game loop... \n"RST);
	game_loop(&game);
	garbco_game(&game);
	return (EXIT_SUCCESS);
}
