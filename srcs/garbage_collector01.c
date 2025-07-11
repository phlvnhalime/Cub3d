/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_collector01.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julcalde <julcalde@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 00:05:27 by julcalde          #+#    #+#             */
/*   Updated: 2025/07/12 00:11:12 by julcalde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

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

