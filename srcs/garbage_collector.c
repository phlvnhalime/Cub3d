/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_collector.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julcalde <julcalde@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 13:55:32 by julcalde          #+#    #+#             */
/*   Updated: 2025/07/03 14:07:26 by julcalde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* Registers all allocated memory and creates a new node that is ready to
register the next pointer. */
void	garbco_add(t_garbco *garbco, void *ptr)
{
	t_garbco_node	*new_node;

	new_node = malloc(sizeof(t_garbco_node));
	new_node->ptr = ptr;
	new_node->next = garbco->head;
	garbco->head = new_node;
}

/* This function read through the list of registered pointer and
deallocates (using free) their memory. */
void	garbco_clean(t_garbco *garbco)
{
	t_garbco_node	*current;
	t_garbco		*tmp;

	current = garbco->head;
	while (current)
	{
		free(current->ptr);
		tmp = current;
		current = current->next;
		free(tmp);
	}
	garbco->head = NULL;
}
