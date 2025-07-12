/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_collector00.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julcalde <julcalde@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 13:55:32 by julcalde          #+#    #+#             */
/*   Updated: 2025/07/12 13:48:04 by julcalde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

/*
	Initializes the garbage collector by setting the head of the linked list
	to NULL. This function should be called before using the garbage collector.
	It ensures that the garbage collector is ready to register pointers.
*/
void	garbco_init(t_garbco *garbco)
{
	if (!garbco)
		return ;
	garbco->head = NULL;
}

/*
	Adds a pointer to the garbage collector.
	It creates a new node, sets its pointer to the given pointer,
	and adds it to the head of the linked list. If the pointer is NULL,
	it does nothing. If memory allocation for the new node fails,
	it frees the given pointer to avoid memory leaks.
*/
void	garbco_add(t_garbco *garbco, void *ptr)
{
	t_garbco_node	*new_node;

	if (!garbco || !ptr)
		return ;
	new_node = malloc(sizeof(t_garbco_node));
	if (!new_node)
	{
		free(ptr);
		return ;
	}
	new_node->ptr = ptr;
	new_node->next = garbco->head;
	garbco->head = new_node;
	DEBUG_PRINT(GRN"Added pointer %p to garbage collector\n"RST, ptr);
}

/*
	Allocates memory using malloc and protects the malloc.
	Registers the pointer in the garbage collector.
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
	Removes a pointer from the garbage collector.
	It searches through the linked list of nodes and removes the node
	that contains the pointer to be removed. If the pointer is not found,
	it prints an error message.
*/
void	garbco_remove(t_garbco *garbco, void *ptr)
{
	t_garbco_node	*current;
	t_garbco_node	*prev;

	if (!garbco || !ptr)
		return ;
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
			DEBUG_PRINT(GRN"Removed pointer %p from garbage collector\n"
				RST, ptr);
			return ;
		}
		prev = current;
		current = current->next;
	}
	DEBUG_PRINT(RD"Pointer %p not found in garbage collector\n"RST, ptr);
}

/*
	Cleans the garbage collector by iterating through the linked list
	of nodes and freeing each pointer and node. It sets the head of the
	linked list to NULL after cleaning up all nodes. It also counts how many
	pointers were cleaned and prints this information.
*/
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
