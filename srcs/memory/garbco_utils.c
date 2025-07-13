/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbco_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julcalde <julcalde@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 14:11:19 by hpehliva          #+#    #+#             */
/*   Updated: 2025/07/13 14:30:08 by julcalde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

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
			DEBUG_PRINT(GRN"Removed pointer %p from garbage collector\n"\
				RST, ptr);
			return ;
		}
		prev = current;
		current = current->next;
	}
	DEBUG_PRINT(RD"Pointer %p not found in garbage collector\n"RST, ptr);
}

// char	*garbco_strdup(t_garbco *garbco, const char *str)
// {
// 	char	*dup;
// 	size_t	len;
// 	size_t	i;

// 	if (!garbco || !str)
// 		return (NULL);
// 	len = strlen(str) + 1;
// 	dup = garbco_malloc(garbco, len);
// 	if (!dup)
// 		return ;
// 	i = 0;
// 	while (str[i])
// 	{
// 		dup[i] = str[i];
// 		i++;
// 	}
// 	dup[i] = '\0';
// 	return (dup);
// }
