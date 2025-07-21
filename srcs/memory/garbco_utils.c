/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbco_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpehliva <hpehliva@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 14:11:19 by hpehliva          #+#    #+#             */
/*   Updated: 2025/07/21 13:13:52 by hpehliva         ###   ########.fr       */
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
		return ;
	new_node->ptr = ptr;
	new_node->next = garbco->head;
	garbco->head = new_node;
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
