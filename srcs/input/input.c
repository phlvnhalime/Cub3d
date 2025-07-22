/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julcalde <julcalde@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 14:59:34 by hpehliva          #+#    #+#             */
/*   Updated: 2025/07/22 20:29:29 by julcalde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

/*
** input_hook - Handles continuous input processing for player movement and
** rotation.
** This function is called repeatedly by the mlx loop to check for key presses
** and update the player's position and rotation accordingly. It also calls
** the raycasting function to render the game world and the minimap rendering
** function to render the minimap.
**
** @param frame Pointer to the game structure containing player and map data.
*/
void	input_hook(void *frame)
{
	t_game	*game;

	game = (t_game *)frame;
	raycast(game);
	render_minimap(game);
	if (mlx_is_key_down(game->mlx, W) || mlx_is_key_down(game->mlx, S)
		|| mlx_is_key_down(game->mlx, A) || mlx_is_key_down(game->mlx, D))
	{
		move_player(game);
	}
	if (mlx_is_key_down(game->mlx, LEFT) || mlx_is_key_down(game->mlx, RIGHT))
	{
		rotate_player(game);
	}
}

/*
** setup_hook - Sets up the input hooks for the game.
** This function registers the input hook for continuous input processing,
** the key hook for handling key events, and the close hook for closing the
** game window. It uses the mlx library to set up these hooks.
**
** @param game Pointer to the game structure containing all game data.
*/
void	setup_hook(t_game *game)
{
	mlx_loop_hook(game->mlx, (input_hook), game);
	mlx_key_hook(game->mlx, handle_key, game);
	mlx_close_hook(game->mlx, close_window, game);
}

/*
** game_loop - Main game loop that sets up hooks and starts the rendering
** process.
** This function initializes the game loop by setting up the input hooks and
** clearing the image pixels. It then calls the raycasting function to render
** the game world and starts the mlx loop to handle events and rendering.
**
** @param game Pointer to the game structure containing all game data.
*/
void	game_loop(t_game *game)
{
	setup_hook(game);
	memset(game->img->pixels, 0, game->img->width * game->img->height
		* sizeof(uint32_t));
	raycast(game);
	mlx_loop(game->mlx);
}
