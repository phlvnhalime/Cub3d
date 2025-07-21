/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_filled_circle.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julcalde <julcalde@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 18:34:00 by julcalde          #+#    #+#             */
/*   Updated: 2025/07/21 18:39:13 by julcalde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

// ORIGINAL VERSION of draw_filled_circle function

// void	draw_filled_circle(t_game *game, int cx, int cy, int radius,
// 	uint32_t color)
// {
// int	px;
// int	py;
// int	x;
// int	y;

// y = -radius;
// while (y <= radius)
// {
// 	x = -radius;
// 	while (x <= radius)
// 	{
// 		if (x * x + y * y <= radius * radius)
// 		{
// 			px = cx + x;
// 			py = cy + y;
// 			if (px >= 0 && px < WIDTH && py >= 0 && py < HEIGHT)
// 				mlx_put_pixel(game->img, px, py, color);
// 		}
// 		x++;
// 	}
// 	y++;
// }
// }

static void	draw_circle_pixels(t_game *game, int *params, uint32_t color)
{
	int	x;
	int	y;
	int	px;
	int	py;

	y = -params[2];
	while (y <= params[2])
	{
		x = -params[2];
		while (x <= params[2])
		{
			if (x * x + y * y <= params[2] * params[2])
			{
				px = params[0] + x;
				py = params[1] + y;
				if (px >= 0 && px < WIDTH && py >= 0 && py < HEIGHT)
					mlx_put_pixel(game->img, px, py, color);
			}
			x++;
		}
		y++;
	}
}

void	draw_filled_circle(t_game *game, int cx, int cy, int radius)
{
	int	params[3];

	params[0] = cx;
	params[1] = cy;
	params[2] = radius;
	draw_circle_pixels(game, params, PLAYER_COLOR);
}
