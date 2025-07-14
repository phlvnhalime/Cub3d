/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils01_parsing.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julcalde <julcalde@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 20:44:45 by hpehliva          #+#    #+#             */
/*   Updated: 2025/07/15 01:13:53 by julcalde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

// For now I'll create a function to remove all ft_split function leak problems.
void	ft_free_split(char **split)
{
	int	i;

	if (!split)
		return ;
	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}
