/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_collector.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julcalde <julcalde@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 13:55:32 by julcalde          #+#    #+#             */
/*   Updated: 2025/07/22 20:32:37 by julcalde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

/*
** garbco_init - Initializes the garbage collector.
** This function initializes the garbage collector by setting the head of the
** linked list to NULL. It should be called before using the garbage collector
** to ensure it is ready to track allocated memory.
**
** @param garbco Pointer to the garbage collector structure to be initialized.
*/
void	garbco_init(t_garbco *garbco)
{
	if (!garbco)
		return ;
	garbco->head = NULL;
}

/*
** garbco_malloc - Allocates memory and adds it to the garbage collector.
** This function allocates memory of the specified size and adds the pointer
** to the garbage collector's linked list. If the allocation fails, it cleans
** up the garbage collector and returns NULL.
**
** @param garbco Pointer to the garbage collector structure.
** @param size Size of memory to allocate.
*/
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

/*
** garbco_clean - Cleans up the garbage collector resources.
** This function iterates through the linked list of garbage collector nodes,
** freeing each node and its associated pointer. It sets the head of the
** garbage collector to NULL after cleaning up all nodes.
**
** @param garbco Pointer to the garbage collector structure containing the head
*/
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

/*
** garbco_delete_txtr - Deletes all textures in the game.
** This function iterates through the textures array in the game structure,
** deleting each texture and setting the texture pointer to NULL. It also
** sets the path pointer to NULL for each texture.
**
** @param game Pointer to the game structure containing all game data.
*/
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

/*
** garbco_game - Cleans up the game resources and terminates the mlx instance.
** This function deletes textures, frees the image, and terminates the mlx
** instance. It also cleans up the garbage collector resources.
**
** @param game Pointer to the game structure containing all game data.
*/
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
