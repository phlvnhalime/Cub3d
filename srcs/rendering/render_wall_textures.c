/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_wall_textures.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julcalde <julcalde@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 21:37:08 by julcalde          #+#    #+#             */
/*   Updated: 2025/07/16 12:58:36 by julcalde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static int	get_valid_wall_dir(t_ray *ray)
{
	int	wall_direction;

	if (!ray->hit)
	{
		DEBUG_PRINT(RD"Ray hit is not found, cannot render texture\n"RST);
	}
	wall_direction = get_wall_direction(ray);
	if (wall_direction < 0 || wall_direction >= 4)
	{
		DEBUG_PRINT(RD"Invalid wall direction: %d\n"RST, wall_direction);
		return (-1);
	}
	return (wall_direction);
}

static mlx_texture_t	*get_texture(t_game *game, int wall_direction)
{
	mlx_texture_t	*tex;

	tex = game->textures[wall_direction].texture;
	if (!tex)
	{
		DEBUG_PRINT(RD"Texture is not found: %d"RST, wall_direction);
	}
	return (tex);
}

static void	handle_missing_texture(t_game *game, t_ray *ray, int x, \
	int wall_direction)
{
	uint32_t	error_color;

	error_color = 0xFFFF00FF;
	draw_vertical_line(game, x, ray->draw_start, ray->draw_end, error_color);
	draw_floor_ceiling(game, x, ray->draw_start, ray->draw_end);
	DEBUG_PRINT(RD"Texture is not found: %d"RST, wall_direction);
}

// Gets wall direction and texture
static mlx_texture_t	*get_wall_texture(t_game *game, t_ray *ray)
{
	mlx_texture_t	*tex;
	int				wall_dir;

	wall_dir = get_valid_wall_dir(ray);
	if (wall_dir == -1)
		return (NULL);
	tex = get_texture(game, wall_dir);
	return (tex);
}

// Calculates texture X coordinate
static int	calc_tex_x(t_game *game, t_ray *ray, mlx_texture_t *tex)
{
	int		tex_x;
	double	wall_x;

	wall_x = get_wall_x(game, ray);
	tex_x = (int)(wall_x * (double)tex->width);
	if ((ray->side == 0 && ray->ray_dir_x > 0) || \
		(ray->side == 1 && ray->ray_dir_y > 0))
		tex_x = tex->width - tex_x - 1;
	return (tex_x);
}

// Calculates texture position and step
static void	calc_tex_pos(t_ray *ray, mlx_texture_t *tex, double *steps, \
	double *tex_pos)
{
	double	step;
	double	pos;

	step = (double)tex->height / (double)ray->line_height;
	pos = (ray->draw_start - HEIGHT / 2 + ray->line_height / 2) * step;
	*steps = step;
	*tex_pos = pos;
}

// Adjusts color for side walls
static uint32_t	shade_color(uint32_t color, int side)
{
	uint8_t	r;
	uint8_t	g;
	uint8_t	b;
	uint8_t	a;

	if (side == 1)
	{
		r = ((color >> 24) & 0xFF) * 0.75;
		g = ((color >> 16) & 0xFF) * 0.75;
		b = ((color >> 8) & 0xFF) * 0.75;
		a = color & 0xFF;
		return (get_rgba_color(r, g, b, a));
	}
	return (color);
}

// Draws a single pixel
static void	put_wall_pixel(t_game *game, t_ray *ray, mlx_texture_t *tex, int x, int y, int tex_x, double tex_pos)
{
	int			tex_y;
	uint32_t	color;

	tex_y = (int)tex_pos;
	if (tex_y >= 0 && tex_y < (int)tex->height)
	{
		color = get_tex_color(tex, tex_x, tex_y);
		color = shade_color(color, ray->side);
		mlx_put_pixel(game->img, x, y, color);
	}
}

// Main rendering function
void	render_textures_wall(t_game *game, t_ray *ray, int x)
{
	mlx_texture_t	*tex;
	int				tex_x;
	int				y;
	double			steps;
	double			tex_pos;

	tex = get_wall_texture(game, ray);
	if (!tex)
	{
		handle_missing_texture(game, ray, x, get_valid_wall_dir(ray));
		return ;
	}
	tex_x = calc_tex_x(game, ray, tex);
	calc_tex_pos(ray, tex, &steps, &tex_pos);
	draw_floor_ceiling(game, x, ray->draw_start, ray->draw_end);
	y = ray->draw_start;
	while (y <= ray->draw_end && y < HEIGHT)
	{
		put_wall_pixel(game, ray, tex, x, y, tex_x, tex_pos);
		tex_pos += steps;
		y++;
	}
}

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

// 	wall_direction = get_valid_wall_dir(ray);
// 	if (wall_direction == -1)
// 		return ;


// 	tex = get_texture(game, wall_direction);
// 	if (!tex)
// 	{
// 		handle_missing_texture(game, ray, x, wall_direction);
// 		return ;
// 	}

// 	wall_x = get_wall_x(game, ray);
// 	tex_x = (int)(wall_x * (double)tex->width);

// 	if ((ray->side == 0 && ray->ray_dir_x > 0) 
// 		|| (ray->side == 1 && ray->ray_dir_y > 0))
// 		tex_x = tex->width - tex_x - 1;

// 	steps = (double)tex->height / (double)ray->line_height;
// 	tex_position = (ray->draw_start - HEIGHT / 2 
// 		+ ray->line_height / 2) * steps;

// 	draw_floor_ceiling(game, x, ray->draw_start, ray->draw_end);

// 	y = ray->draw_start;
// 	while (y <= ray->draw_end && y < HEIGHT)
// 	{
// 		tex_y = (int)tex_position;
// 		if (tex_y >= 0 && tex_y < (int)tex->height)
// 		{

// 			color = get_tex_color(tex, tex_x, tex_y);

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
