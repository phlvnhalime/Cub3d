/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julcalde <julcalde@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 16:00:42 by hpehliva          #+#    #+#             */
/*   Updated: 2025/07/21 18:22:38 by julcalde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

uint32_t	get_rgba_color(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
{
	return ((r << 24) | (g << 16) | (b << 8) | a);
}

uint32_t	get_tex_color(mlx_texture_t *texture, int tex_x, int tex_y)
{
	uint8_t	*pix;
	uint8_t	r;
	uint8_t	g;
	uint8_t	b;
	uint8_t	a;

	if (!texture || tex_x < 0 || tex_x >= (int)texture->width || tex_y < 0
		|| tex_y >= (int)texture->height)
		return (0xFF00FFFF);
	pix = texture->pixels;
	r = pix[(tex_y * (int)texture->width + tex_x) * texture->bytes_per_pixel];
	g = pix[(tex_y * (int)texture->width + tex_x) * texture->bytes_per_pixel
		+ 1];
	b = pix[(tex_y * (int)texture->width + tex_x) * texture->bytes_per_pixel
		+ 2];
	if (texture->bytes_per_pixel == 4)
		a = pix[(tex_y * (int)texture->width + tex_x) * texture->bytes_per_pixel
			+ 3];
	else
		a = 255;
	return (get_rgba_color(r, g, b, a));
}

int	get_wall_direction(t_ray *ray)
{
	if (ray->side == 0)
	{
		if (ray->ray_dir_x > 0)
			return (3);
		else
			return (2);
	}
	else
	{
		if (ray->ray_dir_y > 0)
			return (1);
		else
			return (0);
	}
}

double	get_wall_x(t_game *game, t_ray *ray)
{
	double	wall_x;

	if (ray->side == 0)
		wall_x = game->player.y + ray->perp_wall_dist * ray->ray_dir_y;
	else
		wall_x = game->player.x + ray->perp_wall_dist * ray->ray_dir_x;
	wall_x = wall_x - floor(wall_x);
	return (wall_x);
}

void	draw_square(t_game *game, t_square *sq)
{
	int	i;
	int	j;

	i = 0;
	while (i < sq->size)
	{
		j = 0;
		while (j < sq->size)
		{
			mlx_put_pixel(game->img, sq->x + i, sq->y + j, sq->color);
			j++;
		}
		i++;
	}
}

// Helper function to draw a filled circle with better boundary checks
void	draw_filled_circle(t_game *game, int cx, int cy, int radius,
		uint32_t color)
{
	int	px;
	int	py;
	int	x;
	int	y;

	y = -radius;
	while (y <= radius)
	{
		x = -radius;
		while (x <= radius)
		{
			if (x * x + y * y <= radius * radius)
			{
				px = cx + x;
				py = cy + y;
				if (px >= 0 && px < WIDTH && py >= 0 && py < HEIGHT)
					mlx_put_pixel(game->img, px, py, color);
			}
			x++;
		}
		y++;
	}
}

// Helper function to draw player collision area
void	draw_player_collision_area(t_game *game, int offset_x, int offset_y,
		int cell_size)
{
	double	map_player_x;
	double	map_player_y;
	int		pixel_x;
	int		pixel_y;
	int		buffer_pixels;
	int		px;
	int		py;
	double	buffer;
	int		dx;
	int		dy;

	buffer = 0.2;
	map_player_x = game->player.x;
	map_player_y = game->player.y;
	pixel_x = offset_x + (int)(map_player_x * cell_size);
	pixel_y = offset_y + (int)(map_player_y * cell_size);
	buffer_pixels = (int)(buffer * cell_size);
	dy = -buffer_pixels;
	while (dy <= buffer_pixels)
	{
		dx = -buffer_pixels;
		while (dx <= buffer_pixels)
		{
			px = pixel_x + dx;
			py = pixel_y + dy;
			if (px >= 0 && px < WIDTH && py >= 0 && py < HEIGHT)
			{
				mlx_put_pixel(game->img, px, py, PLAYER_BUFFER_COLOR);
			}
			dx++;
		}
		dy++;
	}
}
