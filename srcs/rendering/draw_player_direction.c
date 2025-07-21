/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_player_direction.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julcalde <julcalde@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 18:06:33 by julcalde          #+#    #+#             */
/*   Updated: 2025/07/21 18:22:55 by julcalde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

// ORIGINAL VERSION of draw_player_direction function

// void	draw_player_direction(t_game *game, int player_cx, int player_cy,
// 		int cell_size)
// {
// 	int	dir_length;
// 	int	end_x;
// 	int	end_y;
// 	int	dx;
// 	int	dy;
// 	int	sx;
// 	int	sy;
// 	int	err;
// 	int	x;
// 	int	y;
// 	int	e2;

// 	dir_length = cell_size;
// 	end_x = player_cx + (int)(game->player.dir_x * dir_length);
// 	end_y = player_cy + (int)(game->player.dir_y * dir_length);
// 	dx = abs(end_x - player_cx);
// 	dy = abs(end_y - player_cy);
// 	sx = (player_cx < end_x) ? 1 : -1;
// 	sy = (player_cy < end_y) ? 1 : -1;
// 	err = dx - dy;
// 	x = player_cx;
// 	y = player_cy;
// 	while (1)
// 	{
// 		if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
// 			mlx_put_pixel(game->img, x, y, DIRECTION_COLOR);
// 		if (x == end_x && y == end_y)
// 			break ;
// 		e2 = 2 * err;
// 		if (e2 > -dy)
// 		{
// 			err -= dy;
// 			x += sx;
// 		}
// 		if (e2 < dx)
// 		{
// 			err += dx;
// 			y += sy;
// 		}
// 	}
// }

static void	init_line_params(t_game *game, int player_cx, int player_cy, \
	int *params)
{
	int	dir_length;

	dir_length = params[0];
	params[1] = player_cx + (int)(game->player.dir_x * dir_length);
	params[2] = player_cy + (int)(game->player.dir_y * dir_length);
	params[3] = abs(params[1] - player_cx);
	params[4] = abs(params[2] - player_cy);
}

static void	calculate_step_direction(int player_cx, int player_cy, \
	int *params, int *steps)
{
	if (player_cx < params[1])
		steps[0] = 1;
	else
		steps[0] = -1;
	if (player_cy < params[2])
		steps[1] = 1;
	else
		steps[1] = -1;
	steps[2] = params[3] - params[4];
}

static void	draw_line_segment(t_game *game, int x, int y, int *line_data)
{
	int	e2;

	if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
		mlx_put_pixel(game->img, x, y, DIRECTION_COLOR);
	if (x == line_data[0] && y == line_data[1])
		return ;
	e2 = 2 * line_data[2];
	if (e2 > -line_data[3])
	{
		line_data[2] -= line_data[3];
		x += line_data[5];
	}
	if (e2 < line_data[4])
	{
		line_data[2] += line_data[4];
		y += line_data[6];
	}
	line_data[7] = x;
	line_data[8] = y;
}

void	draw_player_direction(t_game *game, int player_cx, int player_cy, \
	int cell_size)
{
	int	params[5];
	int	steps[3];
	int	line_data[9];

	params[0] = cell_size;
	init_line_params(game, player_cx, player_cy, params);
	calculate_step_direction(player_cx, player_cy, params, steps);
	line_data[0] = params[1];
	line_data[1] = params[2];
	line_data[2] = steps[2];
	line_data[3] = params[4];
	line_data[4] = params[3];
	line_data[5] = steps[0];
	line_data[6] = steps[1];
	line_data[7] = player_cx;
	line_data[8] = player_cy;
	while (1)
	{
		draw_line_segment(game, line_data[7], line_data[8], line_data);
		if (line_data[7] == line_data[0] && line_data[8] == line_data[1])
			break ;
	}
}
