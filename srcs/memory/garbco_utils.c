/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbco_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julcalde <julcalde@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 14:11:19 by hpehliva          #+#    #+#             */
/*   Updated: 2025/07/18 14:30:12 by julcalde         ###   ########.fr       */
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
		return ;
	}
	new_node->ptr = ptr;
	new_node->next = garbco->head;
	garbco->head = new_node;
	printf("GARB ADD: node=%p, ptr=%p\n", (void *)new_node, ptr);
	DEBUG_PRINT(GRN "Added pointer %p to garbage collector\n" RST, ptr);
}

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
