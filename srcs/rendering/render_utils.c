/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julcalde <julcalde@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 16:00:42 by hpehliva          #+#    #+#             */
/*   Updated: 2025/07/19 10:52:25 by julcalde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

// MLX42 için doğru RGBA renk formatı
#define MAP_WALL_COLOR      0x000000FF
#define MAP_FLOOR_COLOR     0xFFFFFFFF
#define MAP_EMPTY_COLOR     0xC0C0C0FF
#define PLAYER_COLOR        0xFF0000FF
#define DIRECTION_COLOR     0x00FF00FF
#define RAY_COLOR           0xFFFF00FF
#define PLAYER_BUFFER_COLOR 0xFF8000FF

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
static void	draw_filled_circle(t_game *game, int cx, int cy, int radius, uint32_t color)
{
	int	x;
	int	y;
	int	px;
	int	py;

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
static void	draw_player_collision_area(t_game *game, int offset_x, int offset_y, int cell_size)
{
	double	buffer;
	double	map_player_x;
	double	map_player_y;
	int		pixel_x;
	int		pixel_y;
	int		buffer_pixels;
	int		dx;
	int		dy;
	int		px;
	int		py;

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

// Draw player direction line
static void	draw_player_direction(t_game *game, int player_cx, int player_cy, int cell_size)
{
	int	dir_length = cell_size;
	int	end_x = player_cx + (int)(game->player.dir_x * dir_length);
	int	end_y = player_cy + (int)(game->player.dir_y * dir_length);
	int	dx = abs(end_x - player_cx);
	int	dy = abs(end_y - player_cy);
	int	sx = (player_cx < end_x) ? 1 : -1;
	int	sy = (player_cy < end_y) ? 1 : -1;
	int	err = dx - dy;
	int	x = player_cx;
	int	y = player_cy;
	int	e2;

	while (1)
	{
		if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
			mlx_put_pixel(game->img, x, y, DIRECTION_COLOR);
		if (x == end_x && y == end_y)
			break ;
		e2 = 2 * err;
		if (e2 > -dy)
		{
			err -= dy;
			x += sx;
		}
		if (e2 < dx)
		{
			err += dx;
			y += sy;
		}
	}
}

// Draw FOV rays
static void draw_fov_rays(t_game *game, int offset_x, int offset_y, int cell_size)
{
	int		num_rays;
	double	fov;
	double	base_angle;
	double	step;
	int		max_steps;
	double	angle;
	double	dx;
	double	dy;
	double	x;
	double	y;
	int		r;
	int		i;
	int		map_x;
	int		map_y;
	int		draw_x;
	int		draw_y;

	num_rays = 10;
	fov = M_PI / 3;
	base_angle = atan2(game->player.dir_y, game->player.dir_x);
	step = 0.05;
	max_steps = (int)(3.0 / step);
	r = 0;
	while (r < num_rays)
	{
		angle = base_angle + fov * ((double)r / (num_rays - 1) - 0.5);
		dx = cos(angle);
		dy = sin(angle);
		x = game->player.x;
		y = game->player.y;
		i = 0;
		while (i < max_steps)
		{
			map_x = (int)x;
			map_y = (int)y;
			if (map_x < 0 || map_x >= game->map.width || \
				map_y < 0 || map_y >= game->map.height)
				break ;
			if (map_x < (int)strlen(game->map.grid[map_y]) && \
				game->map.grid[map_y][map_x] == '1')
				break ;
			draw_x = offset_x + (int)(x * cell_size);
			draw_y = offset_y + (int)(y * cell_size);
			if (draw_x >= 0 && draw_x < WIDTH && draw_y >= 0 && draw_y < HEIGHT)
				mlx_put_pixel(game->img, draw_x, draw_y, RAY_COLOR);
			x += dx * step;
			y += dy * step;
			i++;
		}
		r++;
	}
}

void render_minimap(t_game *game)
{
	t_square	sq;
	int			map_x;
	int			map_y;
	int			cell_size;
	int			offset_x;
	int			offset_y;
	char		cell;

	cell_size = 10;
	offset_x = 10;
	offset_y = 10;
	map_y = 0;
	while (map_y < game->map.height)
	{
		map_x = 0;
		while (map_x < game->map.width)
		{
			sq.x = offset_x + map_x * cell_size;
			sq.y = offset_y + map_y * cell_size;
			sq.size = cell_size;
			if (map_x < (int)strlen(game->map.grid[map_y]))
			{
				cell = game->map.grid[map_y][map_x];
				if (cell == '1')
					sq.color = MAP_WALL_COLOR;
				else if (cell == '0')
					sq.color = MAP_FLOOR_COLOR;
				else
					sq.color = MAP_EMPTY_COLOR;
			}
			else
			{
				sq.color = MAP_EMPTY_COLOR;
			}
			draw_square(game, &sq);
			map_x++;
		}
		map_y++;
	}
	// Draw FOV rays first (so they appear behind player)
	draw_fov_rays(game, offset_x, offset_y, cell_size);
	// Draw player collision area (optional - uncomment to see collision buffer)
	draw_player_collision_area(game, offset_x, offset_y, cell_size);
	// Calculate exact player position in minimap
	int player_cx = offset_x + (int)(game->player.x * cell_size);
	int player_cy = offset_y + (int)(game->player.y * cell_size);
	// Draw player direction line
	draw_player_direction(game, player_cx, player_cy, cell_size);
	// Draw player circle (on top of everything else)
	int player_radius = cell_size / 3; // Smaller radius for better precision
	draw_filled_circle(game, player_cx, player_cy, player_radius, PLAYER_COLOR);
	// Draw a white center dot for precise positioning
	mlx_put_pixel(game->img, player_cx, player_cy, 0xFFFFFFFF);
}
