/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julcalde <julcalde@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 14:59:34 by hpehliva          #+#    #+#             */
/*   Updated: 2025/07/12 13:52:16 by julcalde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

/*
	- game: A pointer to the game structure containing player and game state
		information.
	- frame: This function is called every frame to handle input.
	
	It checks for key presses and calls the appropriate functions to move or
	rotate the player.
	It also calls the raycasting function to render the frame.
	It uses the MLX library to check for key states and handle input.
*/
void	input_hook(void *frame)
{
	t_game	*game;

	game = (t_game *)frame;
	raycast(game);
	if (mlx_is_key_down(game->mlx, W) || mlx_is_key_down(game->mlx, S) || \
		mlx_is_key_down(game->mlx, A) || mlx_is_key_down(game->mlx, D))
	{
		move_player(game);
	}
	if (mlx_is_key_down(game->mlx, LEFT) || mlx_is_key_down(game->mlx, RIGHT))
	{
		rotate_player(game);
	}
}

/*
	This function handles the key events for the game.
	It checks if the escape key is pressed to close the window,
	and calls the input_hook function to handle other key inputs.
*/
void	setup_hook(t_game *game)
{
	mlx_loop_hook(game->mlx, (input_hook), game);
	mlx_key_hook(game->mlx, handle_key, game);
	mlx_close_hook(game->mlx, close_window, game);
}

/*
	This function is the main game loop.
	It sets up the hooks for input and rendering,
	clears the image pixels, and calls the raycasting function to render the frame.
	Finally, it starts the MLX loop to display the screen.
*/
void	game_loop(t_game *game)
{
	setup_hook(game);
	memset(game->img->pixels, 0, game->img->width * game->img->height * \
		sizeof(uint32_t));
	raycast(game);
	DEBUG_PRINT(GRN"Starting game loop...\n"RST);
	mlx_loop(game->mlx);
}
