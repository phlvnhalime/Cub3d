/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_wall_textures.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpehliva <hpehliva@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 21:37:08 by julcalde          #+#    #+#             */
/*   Updated: 2025/07/21 13:21:43 by hpehliva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static int	get_valid_wall_dir(t_ray *ray)
{
	int	wall_direction;


	wall_direction = get_wall_direction(ray);
	if (wall_direction < 0 || wall_direction >= 4)
		return (-1);
	return (wall_direction);
}

static mlx_texture_t	*get_texture(t_game *game, int wall_direction)
{
	mlx_texture_t	*tex;

	tex = game->textures[wall_direction].texture;
	if (!tex)
		return (NULL);
	return (tex);
}

void	handle_missing_texture(t_game *game, t_ray *ray, int x)
{
	uint32_t	error_color;

	error_color = 0xFFFF00FF;
	draw_vertical_line(game, ray->draw_start, ray->draw_end, error_color);
	draw_floor_ceiling(game, x, ray->draw_start, ray->draw_end);
}

void	render_textures_wall(t_game *game, t_ray *ray, int x)
{
	int				wall_direction;
	mlx_texture_t	*tex;
	double			wall_x;
	int				tex_x;
	double			steps;
	double			tex_position;
	int				y;
	int				tex_y;
	uint32_t		color;
	uint8_t			r;
	uint8_t			g;
	uint8_t			b;
	uint8_t			a;

	wall_direction = get_valid_wall_dir(ray);
	if (wall_direction == -1)
		return ;
	tex = get_texture(game, wall_direction);
	if (!tex)
	{
		handle_missing_texture(game, ray, x);
		return ;
	}
	wall_x = get_wall_x(game, ray);
	tex_x = (int)(wall_x * (double)tex->width);
	if ((ray->side == 0 && ray->ray_dir_x > 0) || (ray->side == 1
			&& ray->ray_dir_y > 0))
		tex_x = tex->width - tex_x - 1;
	steps = (double)tex->height / (double)ray->line_height;
	tex_position = (ray->draw_start - HEIGHT / 2 + ray->line_height / 2)
		* steps;
	draw_floor_ceiling(game, x, ray->draw_start, ray->draw_end);
	y = ray->draw_start;
	while (y <= ray->draw_end && y < HEIGHT)
	{
		tex_y = (int)tex_position;
		if (tex_y >= 0 && tex_y < (int)tex->height)
		{
			color = get_tex_color(tex, tex_x, tex_y);
			if (ray->side == 1)
			{
				r = ((color >> 24) & 0xFF) * 0.75;
				g = ((color >> 16) & 0xFF) * 0.75;
				b = ((color >> 8) & 0xFF) * 0.75;
				a = color & 0xFF;
				color = get_rgba_color(r, g, b, a);
			}
			mlx_put_pixel(game->img, x, y, color);
		}
		tex_position += steps;
		y++;
	}
}
