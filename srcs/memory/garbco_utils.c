/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbco_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julcalde <julcalde@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 14:11:19 by hpehliva          #+#    #+#             */
/*   Updated: 2025/07/22 20:36:53 by julcalde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

/*
** garbco_add - Adds a pointer to the garbage collector.
** It creates a new node, initializes it with the pointer,
** and adds it to the head of the linked list.
** If the garbage collector or the pointer is NULL, it does nothing.
** If memory allocation for the new node fails, it also does nothing.
** This function is used to track dynamically allocated memory
** that should be freed later to prevent memory leaks.
**
** @param garbco Pointer to the garbage collector structure.
** @param ptr Pointer to the memory that should be tracked.
*/
void	garbco_add(t_garbco *garbco, void *ptr)
{
	t_garbco_node	*new_node;

	if (!garbco || !ptr)
		return ;
	new_node = malloc(sizeof(t_garbco_node));
	if (!new_node)
		return ;
	new_node->ptr = ptr;
	new_node->next = garbco->head;
	garbco->head = new_node;
}

/*
** garbco_strdup - Duplicates a string using the garbage collector.
** It allocates memory for the duplicate string using the garbage collector,
** copies the content of the original string into the new memory,
** and returns the pointer to the new string.
** If the garbage collector or the original string is NULL,
** it returns NULL.
** This function is useful for managing string memory in a way
** that ensures the memory can be cleaned up later by the garbage collector.
**
** @param garbco Pointer to the garbage collector structure.
** @param str Pointer to the original string to duplicate.
** @return Pointer to the duplicated string, or NULL if allocation fails.
*/
char	*garbco_strdup(t_garbco *garbco, char *str)
{
	char	*dup;
	size_t	len;
	size_t	i;

	if (!garbco || !str)
		return (NULL);
	len = strlen(str) + 1;
	dup = garbco_malloc(garbco, len);
	if (!dup)
		return (NULL);
	i = 0;
	while (str[i])
	{
		dup[i] = str[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}
