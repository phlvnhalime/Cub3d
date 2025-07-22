/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_textures_wall.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julcalde <julcalde@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 21:37:08 by julcalde          #+#    #+#             */
/*   Updated: 2025/07/23 00:12:37 by julcalde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

// ORIGINAL VERSION of render_textures_wall function

// void	render_textures_wall(t_game *game, t_ray *ray, int x)
// {
// 	int				wall_direction;
// 	mlx_texture_t	*tex;
// 	double			wall_x;
// 	int				tex_x;
// 	double			steps;
// 	double			tex_position;
// 	int				y;
// 	int				tex_y;
// 	uint32_t		color;
// 	uint8_t			r;
// 	uint8_t			g;
// 	uint8_t			b;
// 	uint8_t			a;

	// wall_direction = get_valid_wall_dir(ray);
	// if (wall_direction == -1)
	// 	return ;
	// tex = get_texture(game, wall_direction);
	// if (!tex)
	// {
	// 	handle_missing_texture(game, ray, x);
	// 	return ;
	// }
	// wall_x = get_wall_x(game, ray);
	// tex_x = (int)(wall_x * (double)tex->width);
	// if ((ray->side == 0 && ray->ray_dir_x > 0) || (ray->side == 1
			// && ray->ray_dir_y > 0))
		// tex_x = tex->width - tex_x - 1;
	// steps = (double)tex->height / (double)ray->line_height;
	// tex_position = (ray->draw_start - HEIGHT / 2 + ray->line_height / 2)
	// 	* steps;
	// draw_floor_ceiling(game, x, ray->draw_start, ray->draw_end);
	// y = ray->draw_start;
	// while (y <= ray->draw_end && y < HEIGHT)
	// {
	// 	tex_y = (int)tex_position;
	// 	if (tex_y >= 0 && tex_y < (int)tex->height)
	// 	{
	// 		color = get_tex_color(tex, tex_x, tex_y);
// 			if (ray->side == 1)
// 			{
// 				r = ((color >> 24) & 0xFF) * 0.75;
// 				g = ((color >> 16) & 0xFF) * 0.75;
// 				b = ((color >> 8) & 0xFF) * 0.75;
// 				a = color & 0xFF;
// 				color = get_rgba_color(r, g, b, a);
// 			}
// 			mlx_put_pixel(game->img, x, y, color);
// 		}
// 		tex_position += steps;
// 		y++;
// 	}
// }

/*
** init_texture_params - Initializes the texture parameters
** for rendering the wall texture.
** This function calculates the texture X coordinate, step size
** for the texture Y coordinate, and the current texture Y coordinate.
**
** @param game: Pointer to the game structure containing textures and image.
** @param ray: Pointer to the ray structure containing ray properties.
** @param params: Array to store the texture parameters:
**                [0] - Texture X coordinate,
**                [1] - Step size for texture Y coordinate,
**                [2] - Current texture Y coordinate,
**                [3] - Wall direction (texture index).
** @param tex: Pointer to the texture to be used for rendering.
*/
static void	init_texture_params(t_game *game, t_ray *ray, \
		double *params, mlx_texture_t *tex)
{
	double	wall_x;
	int		tex_x;

	wall_x = get_wall_x(game, ray);
	tex_x = (int)(wall_x * (double)tex->width);
	if ((ray->side == 0 && ray->ray_dir_x > 0) \
		|| (ray->side == 1 && ray->ray_dir_y > 0))
		tex_x = tex->width - tex_x - 1;
	params[0] = tex_x;
	params[1] = ((double)tex->height / (double)ray->line_height);
	params[2] = ((ray->draw_start - HEIGHT / 2 + ray->line_height \
		/ 2) * params[1]);
}

/*
** adjust_wall_color - Adjusts the wall color based on the ray's side.
** If the ray hits a wall on the side, it darkens the color
** to simulate lighting effects.
**
** @param ray: Pointer to the ray structure containing ray properties.
** @param color: Pointer to the color value to adjust.
*/
static void	adjust_wall_color(t_ray *ray, uint32_t *color)
{
	uint8_t	r;
	uint8_t	g;
	uint8_t	b;
	uint8_t	a;

	if (ray->side == 1)
	{
		r = ((*color >> 24) & 0xFF) * 0.75;
		g = ((*color >> 16) & 0xFF) * 0.75;
		b = ((*color >> 8) & 0xFF) * 0.75;
		a = *color & 0xFF;
		*color = get_rgba_color(r, g, b, a);
	}
}

/*
** render_wall_pixels - Renders the wall pixels for a given ray.
** This function calculates the texture coordinates and renders
** the wall pixels based on the ray's properties and the texture.
**
** @param game: Pointer to the game structure containing textures and image.
** @param ray: Pointer to the ray structure containing ray properties.
** @param x: The x-coordinate of the pixel column to render.
** @param params: Array containing texture parameters:
**                [0] - Texture X coordinate,
**                [1] - Step size for texture Y coordinate,
**                [2] - Current texture Y coordinate,
**                [3] - Wall direction (texture index).
*/
static void	render_wall_pixels(t_game *game, t_ray *ray, int x, double *params)
{
	int				y;
	int				tex_y;
	uint32_t		color;
	mlx_texture_t	*tex;

	tex = game->textures[(int)params[3]].texture;
	draw_floor_ceiling(game, x, ray->draw_start, ray->draw_end);
	y = ray->draw_start;
	while (y <= ray->draw_end && y < HEIGHT)
	{
		tex_y = params[2];
		if (tex_y >= 0 && tex_y < (int)tex->height)
		{
			color = get_tex_color(tex, params[0], tex_y);
			adjust_wall_color(ray, &color);
			mlx_put_pixel(game->img, x, y, color);
		}
		params[2] += params[1];
		y++;
	}
}

/*
** render_textures_wall - Renders the wall textures for a given ray.
** This function calculates the texture coordinates and renders
** the wall pixels based on the ray's properties and the texture.
**
** @param game: Pointer to the game structure containing textures and image.
** @param ray: Pointer to the ray structure containing ray properties.
** @param x: The x-coordinate of the pixel column to render.
*/
void	render_textures_wall(t_game *game, t_ray *ray, int x)
{
	int				wall_direction;
	mlx_texture_t	*tex;
	double			params[4];

	wall_direction = get_valid_wall_dir(ray);
	if (wall_direction == -1)
		return ;
	tex = get_texture(game, wall_direction);
	if (!tex)
	{
		handle_missing_texture(game, ray, x);
		return ;
	}
	params[3] = wall_direction;
	init_texture_params(game, ray, params, tex);
	render_wall_pixels(game, ray, x, params);
}
