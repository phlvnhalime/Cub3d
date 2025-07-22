/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julcalde <julcalde@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 16:00:42 by hpehliva          #+#    #+#             */
/*   Updated: 2025/07/23 00:14:29 by julcalde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

/*
** get_rgba_color - Constructs a 32-bit color value from RGBA components.
** This function takes individual color components (red, green, blue, alpha)
** and combines them into a single 32-bit unsigned integer.
**
** @param r - Red component (0-255).
** @param g - Green component (0-255).
** @param b - Blue component (0-255).
** @param a - Alpha component (0-255).
*/
uint32_t	get_rgba_color(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
{
	return ((r << 24) | (g << 16) | (b << 8) | a);
}

/*
** get_tex_color - Retrieves the color of a pixel from a texture.
** This function calculates the pixel's position in the texture
** based on the texture coordinates and returns the color
** as a 32-bit unsigned integer.
**
** @param texture - Pointer to the texture structure containing pixel data.
** @param tex_x - The X coordinate of the texture pixel.
** @param tex_y - The Y coordinate of the texture pixel.
** @return - Returns the color of the pixel as a 32-bit unsigned integer.
**           If the texture is NULL or coordinates are out of bounds,
**           it returns a default color (0xFF00FFFF).
*/
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

/*
** get_wall_direction - Determines the wall direction based on ray side.
** This function checks the ray's side and direction to determine
** the wall direction.
**
** @param ray - Pointer to the ray structure containing ray direction and side.
** @return - Returns an integer representing the wall direction:
**           0 for North, 1 for South, 2 for East, and 3 for West.
*/
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

/*
** get_wall_x - Calculates the X coordinate of the wall hit.
** This function determines the X coordinate of the wall hit
** based on the ray's direction and the perpendicular distance
** to the wall.
**
** @param game - Pointer to the game structure containing player position.
** @param ray - Pointer to the ray structure containing ray direction
** @return - Returns the X coordinate of the wall hit as a double.
*/
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

/*
** draw_square - Draws a square on the game image.
** This function iterates over the pixels of the square
** and sets their color in the game image.
**
** @param game - Pointer to the game structure containing the image.
** @param sq - Pointer to the square structure containing
*/
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
