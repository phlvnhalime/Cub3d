/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpehliva <hpehliva@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 11:52:07 by hpehliva          #+#    #+#             */
/*   Updated: 2025/07/21 15:49:34 by hpehliva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	draw_vertical_line(t_game *game, int start, int end, uint32_t color)
{
	int	y;
	int	x;

	x = 0;
	y = start;
	while (y <= end && y < HEIGHT)
	{
		if (y >= 0 && x >= 0 && x < WIDTH)
			mlx_put_pixel(game->img, x, y, color);
		y++;
	}
}

void	draw_floor_ceiling(t_game *game, int x, int wall_start, int wall_end)
{
	int			y;
	uint32_t	ceiling_color;
	uint32_t	floor_color;

	ceiling_color = get_rgba_color(game->ceiling_color.r, game->ceiling_color.g,
			game->ceiling_color.b, 255);
	y = 0;
	while (y < wall_start && y < HEIGHT)
	{
		if (x >= 0 && x < WIDTH && y >= 0)
			mlx_put_pixel(game->img, x, y, ceiling_color);
		y++;
	}
	floor_color = get_rgba_color(game->floor_color.r, game->floor_color.g,
			game->floor_color.b, 255);
	y = wall_end + 1;
	while (y < HEIGHT)
	{
		if (x >= 0 && x < WIDTH && y >= 0)
			mlx_put_pixel(game->img, x, y, floor_color);
		y++;
	}
}

void	render_frame(t_game *game)
{
	raycast(game);
	render_minimap(game);
}
