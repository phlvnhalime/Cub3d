/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_player_collision_area.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julcalde <julcalde@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 18:26:10 by julcalde          #+#    #+#             */
/*   Updated: 2025/07/21 18:30:29 by julcalde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

// ORIGINAL VERSION of draw_player_collision_area

// void	draw_player_collision_area(t_game *game, int offset_x, int offset_y,
// 		int cell_size)
// {
// 	double	map_player_x;
// 	double	map_player_y;
// 	int		pixel_x;
// 	int		pixel_y;
// 	int		buffer_pixels;
// 	int		px;
// 	int		py;
// 	double	buffer;
// 	int		dx;
// 	int		dy;

// 	buffer = 0.2;
// 	map_player_x = game->player.x;
// 	map_player_y = game->player.y;
// 	pixel_x = offset_x + (int)(map_player_x * cell_size);
// 	pixel_y = offset_y + (int)(map_player_y * cell_size);
// 	buffer_pixels = (int)(buffer * cell_size);
// 	dy = -buffer_pixels;
// 	while (dy <= buffer_pixels)
// 	{
// 		dx = -buffer_pixels;
// 		while (dx <= buffer_pixels)
// 		{
// 			px = pixel_x + dx;
// 			py = pixel_y + dy;
// 			if (px >= 0 && px < WIDTH && py >= 0 && py < HEIGHT)
// 			{
// 				mlx_put_pixel(game->img, px, py, PLAYER_BUFFER_COLOR);
// 			}
// 			dx++;
// 		}
// 		dy++;
// 	}
// }

static void	init_collision_params(t_game *game, int cell_size, int *params)
{
	double	buffer;
	int		pixel_x;
	int		pixel_y;

	buffer = 0.2;
	pixel_x = params[0] + (int)(game->player.x * cell_size);
	pixel_y = params[1] + (int)(game->player.y * cell_size);
	params[2] = pixel_x;
	params[3] = pixel_y;
	params[4] = (int)(buffer * cell_size);
}

static void	draw_collision_grid(t_game *game, int *params)
{
	int	dx;
	int	dy;
	int	px;
	int	py;

	dy = -params[4];
	while (dy <= params[4])
	{
		dx = -params[4];
		while (dx <= params[4])
		{
			px = params[2] + dx;
			py = params[3] + dy;
			if (px >= 0 && px < WIDTH && py >= 0 && py < HEIGHT)
				mlx_put_pixel(game->img, px, py, PLAYER_BUFFER_COLOR);
			dx++;
		}
		dy++;
	}
}

void	draw_player_collision_area(t_game *game, int offset_x, \
	int offset_y, int cell_size)
{
	int	params[5];

	params[0] = offset_x;
	params[1] = offset_y;
	init_collision_params(game, cell_size, params);
	draw_collision_grid(game, params);
}
