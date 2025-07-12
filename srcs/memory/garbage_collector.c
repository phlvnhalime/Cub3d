/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_collector.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpehliva <hpehliva@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 13:55:32 by julcalde          #+#    #+#             */
/*   Updated: 2025/07/09 14:59:48 by hpehliva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

/*
	Initialize garbage collector.
*/

void garbco_init(t_garbco *garbco)
{
	if(!garbco)
		return;
	garbco->head = NULL;
}

/* Registers all allocated memory and creates a new node that is ready to
register the next pointer. */
void	garbco_add(t_garbco *garbco, void *ptr)
{
	t_garbco_node	*new_node;

	if (!garbco || !ptr)
		return;
	new_node = malloc(sizeof(t_garbco_node));
	if (!new_node)
	{
		free(ptr);
		return;
	}
	new_node->ptr = ptr;
	new_node->next = garbco->head;
	garbco->head = new_node;
	DEBUG_PRINT(GRN"Added pointer %p to garbage collector\n"RST, ptr);
}

/*
	Safe malloc automaticly
*/
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

/*
	Remove specific pointer from the garbage collector.
*/

void garbco_remove(t_garbco *garbco, void *ptr)
{
	t_garbco_node	*current;
	t_garbco_node	*prev;

	if (!garbco || !ptr)
		return;
	current = garbco->head;
	prev = NULL;
	while (current)
	{
		if (current->ptr == ptr)
		{
			if (prev)
				prev->next = current->next;
			else
				garbco->head = current->next;
			free(current);
			DEBUG_PRINT(GRN"Removed pointer %p from garbage collector\n"RST, ptr);
			return;
		}
		prev = current;
		current = current->next;
	}
	DEBUG_PRINT(RD"Pointer %p not found in garbage collector\n"RST, ptr);
}


/* This function read through the list of registered pointer and
deallocates (using free) their memory. */
void	garbco_clean(t_garbco *garbco)
{
	t_garbco_node	*current;
	t_garbco_node		*tmp;
	int count;

	if(!garbco)
		return;
	DEBUG_PRINT(GRN"Cleaning garbage collector...\n"RST);
	current = garbco->head;
	count = 0;
	while (current)
	{
		tmp = current->next;
		// Sadece NULL olmayan pointer'ları temizle
		if(current->ptr != NULL)
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

void garbco_game(t_game *game)
{
	if(!game)
		return;
	
	DEBUG_PRINT(GRN"Cleaning game garbage collector...\n"RST);
	int i = 0;
	while(i < 4)
	{
		if(game->textures[i].texture)
		{
			mlx_delete_texture(game->textures[i].texture);
			game->textures[i].texture = NULL;
		}
		if(game->textures[i].path)
			game->textures[i].path = NULL;
		i++;
		DEBUG_PRINT(GRN"Texture %d cleaned\n"RST, i);
	}
	if(game->img)
	{
		mlx_delete_image(game->mlx, game->img);
		game->img = NULL;
		DEBUG_PRINT(GRN"Image cleaned\n"RST);
	}
	if(game->mlx)
	{
		mlx_terminate(game->mlx);
		game->mlx = NULL;
		DEBUG_PRINT(GRN"MLX cleaned\n"RST);
	}

	garbco_clean(&game->garbco);
	DEBUG_PRINT(GRN"Game garbage collector cleaned\n"RST);
}
