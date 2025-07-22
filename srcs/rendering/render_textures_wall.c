/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_textures_wall.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julcalde <julcalde@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 21:37:08 by julcalde          #+#    #+#             */
/*   Updated: 2025/07/22 15:22:00 by julcalde         ###   ########.fr       */
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

static void	init_texture_params(t_game *game, t_ray *ray, \
		int *params, mlx_texture_t *tex)
{
	double	wall_x;
	int		tex_x;

	wall_x = get_wall_x(game, ray);
	tex_x = (int)(wall_x * (double)tex->width);
	if ((ray->side == 0 && ray->ray_dir_x > 0) \
		|| (ray->side == 1 && ray->ray_dir_y > 0))
		tex_x = tex->width - tex_x - 1;
	params[0] = tex_x; // tex_x
	params[1] = (int)((double)tex->height / (double)ray->line_height * 1000); // steps (scaled)
	params[2] = (int)((ray->draw_start - HEIGHT / 2 + ray->line_height / 2) * params[1] / 1000); // tex_position (scaled)
}

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

static void	render_wall_pixels(t_game *game, t_ray *ray, int x, int *params)
{
	int				y;
	int				tex_y;
	uint32_t		color;
	mlx_texture_t	*tex;

	tex = game->textures[params[3]].texture; // wall_direction
	draw_floor_ceiling(game, x, ray->draw_start, ray->draw_end);
	y = ray->draw_start;
	while (y <= ray->draw_end && y < HEIGHT)
	{
		tex_y = params[2] / 1000; // tex_position (unscaled)
		if (tex_y >= 0 && tex_y < (int)tex->height)
		{
			color = get_tex_color(tex, params[0], tex_y); // tex_x
			adjust_wall_color(ray, &color);
			mlx_put_pixel(game->img, x, y, color);
		}
		params[2] += params[1]; // tex_position += steps
		y++;
	}
}

void	render_textures_wall(t_game *game, t_ray *ray, int x)
{
	int				wall_direction;
	mlx_texture_t	*tex;
	int				params[4]; // tex_x, steps, tex_position, wall_direction

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
