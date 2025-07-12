/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julcalde <julcalde@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 11:52:07 by hpehliva          #+#    #+#             */
/*   Updated: 2025/07/12 12:23:23 by julcalde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

// Orientation wall
int	get_wall_direction(t_ray *ray)
{
	if (ray->side == 0)
	{
		if (ray->ray_dir_x > 0)
			return (3);// east (EA)
		else
			return (2);//west(WE)
	}
	else
	{
		if (ray->ray_dir_y > 0) //south (SO)
			return (1);
		else
			return (0); // north (NO)
	}
}

// Calculate textures
double	get_wall_x(t_game *game, t_ray *ray)
{
	double	wall_x;

	if (ray->side == 0)
		wall_x = game->player.y + ray->perp_wall_dist * ray->ray_dir_y;
	else
		wall_x = game->player.x + ray->perp_wall_dist * ray->ray_dir_x;
	wall_x = wall_x - floor(wall_x); // Just takes franctional part
	return (wall_x);
}

uint32_t	get_rgba_color(uint8_t r,uint8_t g, uint8_t b, uint8_t a)
{
	return ((r << 24) | (g << 16) | (b << 8) | a);
}

uint32_t	get_tex_color(mlx_texture_t *texture, int tex_x, int tex_y)
{
	int		pix_index;
	uint8_t	r;
	uint8_t	g;
	uint8_t	b;
	uint8_t	a;
	uint8_t	*pix;

	if (!texture || tex_x < 0 || tex_x >= (int)texture->width || tex_y < 0 || tex_y >= (int)texture->height)
		return (0xFF00FFFF); //(RED) // Search it which color you can use! // TODO
	pix_index = (tex_y * (int)texture->width + tex_x) * texture->bytes_per_pixel;
	pix = texture->pixels;

	r = pix[pix_index];
	g = pix[pix_index + 1];
	b = pix[pix_index+ 2];
	if (texture->bytes_per_pixel == 4)
		a = pix[pix_index+3];
	else
		a = 255;
	return (get_rgba_color(r, g, b, a));
}

// Draw vertical
void	draw_vertical_line(t_game *game, int x, int start, int end, uint32_t color)
{
	int	y;

	y = start;
	while (y <= end && y < HEIGHT)
	{
		if (y >= 0 && x >= 0 && x < WIDTH)
			mlx_put_pixel(game->img, x, y, color);
		y++;
	}
}

// horizontal
void	draw_floor_ceiling(t_game *game, int x, int wall_start, int wall_end)
{
	int			y;
	uint32_t	ceiling_color;
	uint32_t	floor_color;

	ceiling_color = get_rgba_color(game->ceiling_color.r, \
		game->ceiling_color.g, game->ceiling_color.b, 255);
	y = 0;
	while (y < wall_start && y < HEIGHT)
	{
		if (x >= 0 && x < WIDTH && y >= 0)
			mlx_put_pixel(game->img, x, y, ceiling_color);
		y++;
	}
	floor_color = get_rgba_color(game->floor_color.r, \
		game->floor_color.g, game->floor_color.b, 255);
	y = wall_end + 1;
	while (y < HEIGHT)
	{
		if (x >= 0 && x < WIDTH && y >= 0)
			mlx_put_pixel(game->img, x, y, floor_color);
		y++;
	}
}

void	render_textures_wall(t_game *game, t_ray *ray, int x)
{
	int				wall_direction;
	mlx_texture_t	*tex;
	uint32_t		error_color;
	double			wall_x;
	int				tex_x;
	int				tex_y;
	double			steps;
	double			tex_position;
	int				y;
	uint32_t		color;
	uint8_t			r;
	uint8_t			g;
	uint8_t			b;
	uint8_t			a;

	// Determine which wall direction to use
	if (!ray->hit)
	{
		DEBUG_PRINT(RD"Ray hit is not found, cannot render texture\n"RST);
		return ;
	}
	wall_direction = get_wall_direction(ray);
	if (wall_direction < 0 || wall_direction >= 4)
	{
		DEBUG_PRINT(RD"Invalid wall direction: %d\n"RST, wall_direction);
		return ;
	}
	tex = game->textures[wall_direction].texture;
	if (!tex)
	{
		DEBUG_PRINT(RD"Texture is not found: %d"RST, wall_direction);
		error_color = 0xFFFF00FF; // Yellow color for error
		draw_vertical_line(game, x, ray->draw_start, ray->draw_end, \
			error_color);
		draw_floor_ceiling(game, x, ray->draw_start, ray->draw_end);
		return ;
	}
	// Calculate the cordinate on the wall
	wall_x = get_wall_x(game, ray);
	tex_x = (int)(wall_x * (double)tex->width);
	if ((ray->side == 0 && ray->ray_dir_x > 0) || \
		(ray->side == 1 && ray->ray_dir_y > 0))
		tex_x = tex->width - tex_x - 1;
	// parameters
	steps = (double)tex->height / (double)ray->line_height;
	tex_position = (ray->draw_start - HEIGHT / 2 + ray->line_height / 2) \
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
				// darken horizontal walls by %25 
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
