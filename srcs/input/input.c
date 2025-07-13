/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpehliva <hpehliva@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 14:59:34 by hpehliva          #+#    #+#             */
/*   Updated: 2025/07/12 14:12:30 by hpehliva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

/*
    I need to create all keys with hook and all mouse with hook
*/

void	input_hook(void *frame)
{
	t_game *game = (t_game *)frame;
    raycast(game);
	if(mlx_is_key_down(game->mlx, W) ||mlx_is_key_down(game->mlx, S) ||mlx_is_key_down(game->mlx, A) ||mlx_is_key_down(game->mlx, D))
    {
        move_player(game);
    }
    if(mlx_is_key_down(game->mlx, LEFT) ||mlx_is_key_down(game->mlx, RIGHT))
    {
        rotate_player(game);
    }
        
}

void	setup_hook(t_game *game){
    mlx_loop_hook(game->mlx, (input_hook), game);
	// mlx_loop_hook(game->mlx, (render_frame), game);
	mlx_key_hook(game->mlx, handle_key, game); 
	mlx_close_hook(game->mlx, close_window, game);
}

void game_loop(t_game *game)
{
	setup_hook(game); 
	memset(game->img->pixels, 0, game->img->width * game->img->height * sizeof(uint32_t));
	raycast(game); // Raycasting function to render the frame
	DEBUG_PRINT(GRN"Starting game loop...\n"RST);
	mlx_loop(game->mlx); // Open the screen or show the screen
}