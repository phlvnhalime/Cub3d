/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julcalde <julcalde@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 11:52:07 by hpehliva          #+#    #+#             */
/*   Updated: 2025/07/23 00:17:02 by julcalde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

/*
** draw_vertical_line - Draws a vertical line on the image.
** This function fills a vertical line from the start y-coordinate to the end
** y-coordinate with a specified color.
** It uses the mlx_put_pixel function to draw pixels on the image.
**
** @param game - Pointer to the game structure containing all necessary data.
** @param start - The starting y-coordinate of the vertical line.
** @param end - The ending y-coordinate of the vertical line.
** @param color - The color to fill the vertical line with, represented as a
** 32-bit integer.
** @note It ensures that the coordinates are within the bounds of the image
** dimensions.
*/
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

/*
** draw_floor_ceiling - Draws the floor and ceiling for a given column.
** This function fills the area above the wall with the ceiling color
** and the area below the wall with the floor color.
** It calculates the colors based on the game's ceiling and floor color settings.
** It uses the mlx_put_pixel function to draw pixels on the image.
**
** @param game - Pointer to the game structure containing all necessary data.
** @param x - The x-coordinate of the column to draw.
** @param wall_start - The y-coordinate where the wall starts (top of the wall).
** @param wall_end - The y-coordinate where the wall ends (bottom of the wall).
*/
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

/*
** render_frame - Renders the current frame of the game.
** This function is responsible for
** performing raycasting to determine what to draw,
** drawing the floor and ceiling,
** and rendering the minimap.
** It calls the raycast function to perform the raycasting,
** draws the floor and ceiling for each column,
** and finally renders the minimap.
** It is called every frame to update the display.
**
** @param game - Pointer to the game structure containing all necessary data.
*/
void	render_frame(t_game *game)
{
	raycast(game);
	render_minimap(game);
}
