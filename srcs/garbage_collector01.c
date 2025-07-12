/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_collector01.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julcalde <julcalde@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 00:05:27 by julcalde          #+#    #+#             */
/*   Updated: 2025/07/12 15:51:02 by julcalde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

/*
	* This function cleans the resources used by the game.
	* It deletes the image associated with the game and terminates the MLX instance.
	* It also sets the image pointer to NULL and prints a debug message.
	* Finally, it sets the MLX pointer to NULL and prints another debug message.
	Note: This function is called when the game is closed or when the resources
	are no longer needed to free up memory and avoid memory leaks.
	* @param game: Pointer to the game structure containing the resources to clean.
	* If the game or its resources are NULL, it does nothing.
*/
void	garbco_cleanup_rsrcs(t_game *game)
{
	if (game->img)
	{
		mlx_delete_image(game->mlx, game->img);
		game->img = NULL;
		DEBUG_PRINT(GRN"Image cleaned\n"RST);
	}
	if (game->mlx)
	{
		mlx_terminate(game->mlx);
		game->mlx = NULL;
		DEBUG_PRINT(GRN"MLX cleaned\n"RST);
	}
}

/*
	* This function cleans the game garbage collector.
	* It iterates through the textures array, deleting each texture
	* and setting the path to NULL.
	* It also calls the garbco_cleanup_rsrcs function to clean up
	* the image and MLX resources.
	* Finally, it calls the garbco_clean function to clean the garbage collector
	* and prints debug messages indicating the cleaning process.
	* @param game: Pointer to the game structure containing the textures and 
	* resources. If the game is NULL, it does nothing.
*/
void	garbco_game(t_game *game)
{
	int	i;

	if (!game)
		return ;
	DEBUG_PRINT(GRN"Cleaning game garbage collector...\n"RST);
	i = 0;
	while (i < 4)
	{
		if (game->textures[i].texture)
		{
			mlx_delete_texture(game->textures[i].texture);
			game->textures[i].texture = NULL;
		}
		if (game->textures[i].path)
			game->textures[i].path = NULL;
		i++;
		DEBUG_PRINT(GRN"Texture %d cleaned\n"RST, i);
	}
	garbco_cleanup_rsrcs(game);
	garbco_clean(&game->garbco);
	DEBUG_PRINT(GRN"Game garbage collector cleaned\n"RST);
}
