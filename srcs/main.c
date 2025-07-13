/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpehliva <hpehliva@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 11:49:13 by hpehliva          #+#    #+#             */
/*   Updated: 2025/07/12 16:36:53 by hpehliva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	close_window(void *frame)
{
	t_game *game = (t_game *)frame;
	DEBUG_PRINT(YLW"Window close required\n"RST); 
	garbco_game(game);
	mlx_close_window(game->mlx);
}

int	main(int ac, char **av)
{
	t_game game;

	// If is it successful, we can now initialize the game window
	if (!validate_args(ac, av))
		return (EXIT_FAILURE);
	
	init_game(&game);
	
	/*Parse arguments and set up game*/
	if (!parse_file(&game, av[1]))
	{
		return (EXIT_FAILURE);
	}

	DEBUG_PRINT(GRN"Starting game loop... \n"RST);
	game_loop(&game);
	garbco_game(&game);
	return (EXIT_SUCCESS);
}

