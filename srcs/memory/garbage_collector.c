/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_collector.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpehliva <hpehliva@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 13:55:32 by julcalde          #+#    #+#             */
/*   Updated: 2025/07/21 16:42:58 by hpehliva         ###   ########.fr       */
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

	ptr = NULL;
	if (!garbco || size == 0)
		return (NULL);
	ptr = malloc(size);
	if (!ptr)
	{
		garbco_clean(garbco);
		return (NULL);
	}
	garbco_add(garbco, ptr);
	return (ptr);
}

// ORIGINALLY from garbco_clean function. Moved to garbco_utils.c
// 
// void	free_garbco_node(t_garbco_node *current, int *count)
// {
// 	if (current->ptr != NULL)
// 	{
// 		printf("GARB FREE: node=%p, ptr=%p\n", (void *)current, current->ptr);
// 		DEBUG_PRINT(YLW "Pointer %p is being freed...\n" RST, current->ptr);
// 		count++;
// 		free(current->ptr);
// 	}
// 	else
// 	{
// 		printf("GARB FREE: node=%p, ptr=NULL\n", (void *)current);
// 		DEBUG_PRINT(YLW "Pointer is NULL, skipping free...\n" RST);
// 	}
// 	free(current);
// }

void	garbco_clean(t_garbco *garbco)
{
	t_garbco_node	*current;
	t_garbco_node	*tmp;

	if (!garbco)
		return ;
	current = garbco->head;
	while (current)
	{
		tmp = current->next;
		if (current->ptr != NULL)
			free(current->ptr);
		free(current);
		current = tmp;
	}
	garbco->head = NULL;
}

void	garbco_delete_txtr(t_game *game)
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
	}
}

void	garbco_game(t_game *game)
{
	if (!game)
		return ;
	garbco_delete_txtr(game);
	if (game->img)
	{
		mlx_delete_image(game->mlx, game->img);
		game->img = NULL;
	}
	if (game->mlx)
	{
		mlx_terminate(game->mlx);
		game->mlx = NULL;
	}
	garbco_clean(&game->garbco);
}
