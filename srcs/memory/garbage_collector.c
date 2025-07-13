/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_collector.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julcalde <julcalde@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 13:55:32 by julcalde          #+#    #+#             */
/*   Updated: 2025/07/13 14:14:35 by julcalde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	garbco_init(t_garbco *garbco)
{
	if (!garbco)
		return ;
	garbco->head = NULL;
}

void	*garbco_malloc(t_garbco *garbco, size_t size)
{
	void	*ptr;

	if (!garbco || size == 0)
		return (NULL);
	ptr = malloc(size);
	if (!ptr)
	{
		DEBUG_PRINT(RD"Memory allocation failed for size %zu\n"RST, size);
		return (NULL);
	}
	garbco_add(garbco, ptr);
	DEBUG_PRINT(GRN"Allocated %zu bytes at %p\n"RST, size, ptr);
	return (ptr);
}

void	garbco_clean(t_garbco *garbco)
{
	t_garbco_node	*current;
	t_garbco_node	*tmp;
	int				count;

	if (!garbco)
		return ;
	DEBUG_PRINT(GRN"Cleaning garbage collector...\n"RST);
	current = garbco->head;
	count = 0;
	while (current)
	{
		tmp = current->next;
		if (current->ptr != NULL)
		{
			DEBUG_PRINT(YLW"Pointer %p is NULL, skipping...\n"RST, current->ptr);
			free(current->ptr);
			count++;
		}
		else
			DEBUG_PRINT(YLW"Pointer %p is NULL, skipping...\n"RST, current->ptr);
		free(current);
		current = tmp;
	}
	garbco->head = NULL;
	DEBUG_PRINT(GRN"Garbage collector cleaned %d pointers\n"RST, count);
}

static void	garbco_delete_txtr(t_game *game)
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

void	garbco_game(t_game *game)
{
	if (!game)
		return ;
	DEBUG_PRINT(GRN"Cleaning game garbage collector...\n"RST);
	garbco_delete_txtr(game);
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
