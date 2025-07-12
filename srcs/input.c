/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julcalde <julcalde@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 14:59:34 by hpehliva          #+#    #+#             */
/*   Updated: 2025/07/12 16:03:09 by julcalde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

/*
	* This function is called every frame to handle input and update the game 
	* state. It performs raycasting to render the scene and checks for player 
	* movement and rotation based on key presses.
	* @param frame: Pointer to the game structure containing the game state.
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
	* This function handles the key events for the game.
	* It checks if the escape key is pressed to close the window,
	* and calls the input_hook function to handle other key inputs.
	* @param keydata: The key data structure containing information about the 
	* key event.
*/
void	setup_hook(t_game *game)
{
	mlx_loop_hook(game->mlx, (input_hook), game);
	mlx_key_hook(game->mlx, handle_key, game);
	mlx_close_hook(game->mlx, close_window, game);
}

/*
	* This function is the main game loop.
	* It sets up the hooks for input and rendering,
	* clears the image pixels, and calls the raycasting function to render the 
	* frame.
	* Finally, it starts the MLX loop to display the screen.
	* @param game: Pointer to the game structure containing the game state.
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
