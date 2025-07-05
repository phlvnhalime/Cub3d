/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_collector01.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julcalde <julcalde@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 11:30:57 by julcalde          #+#    #+#             */
/*   Updated: 2025/07/05 11:39:13 by julcalde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static void	garbco_clean_textures(t_game *game)
{
	int	i;

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
}

/*
	Dinamically allocated resources are freed and set to NULL.
*/
void	garbco_game(t_game *game)
{
	if (!game)
		return ;
	DEBUG_PRINT(GRN"Cleaning game garbage collector...\n"RST);
	garbco_clean_textures(game);
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
	garbco_clean(&game->garbco);
	DEBUG_PRINT(GRN"Game garbage collector cleaned\n"RST);
}
