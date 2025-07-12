/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpehliva <hpehliva@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 16:00:42 by hpehliva          #+#    #+#             */
/*   Updated: 2025/07/12 16:00:58 by hpehliva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	render_frame(void *frame)
{
	t_game *game = (t_game *)frame;
	// Clean the screen for black background
	// memset(game->img->pixels... )
	raycast(game);
	DEBUG_PRINT(GRN"Frame rendered\n"RST);
}