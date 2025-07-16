/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpehliva <hpehliva@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 11:52:07 by hpehliva          #+#    #+#             */
/*   Updated: 2025/07/16 10:25:04 by hpehliva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

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

	floor_color = get_rgba_color (game->floor_color.r, \
		game->floor_color.g, game->floor_color.b, 255);

	y = wall_end + 1;
	while (y < HEIGHT)
	{
		if (x >= 0 && x < WIDTH && y >= 0)
			mlx_put_pixel(game->img, x, y, floor_color);
		y++;
	}
}

// static void	validate_ray_hit(t_ray *ray)
// {
// 	if (!ray->hit)
// 	{
// 		DEBUG_PRINT(RD"Ray hit is not found, cannot render texture\n"RST);
// 	}
// }

// static int	get_valid_wall_dir(t_ray *ray)
// {
// 	int	wall_direction;

// 	wall_direction = get_wall_direction(ray);
// 	if (wall_direction < 0 || wall_direction >= 4)
// 	{
// 		DEBUG_PRINT(RD"Invalid wall direction: %d\n"RST, wall_direction);
// 		return (-1);
// 	}
// 	return (wall_direction);
// }

// void	render_textures_wall(t_game *game, t_ray *ray, int x)
// {
// 	int				wall_direction;
// 	mlx_texture_t	*tex;
// 	uint32_t		error_color;

// 	validate_ray_hit(ray);
// 	wall_direction = get_valid_wall_dir(ray);
// 	if (wall_direction == -1)
// 		return ;
// 	tex = game->textures[wall_direction].texture;
// 	if (!tex)
// 	{
// 		DEBUG_PRINT(RD"Texture is not found: %d"RST, wall_direction);
// 		error_color = 0xFFFF00FF;
// 		draw_vertical_line(game, x, ray->draw_start, ray->draw_end, \
// 			error_color);
// 		draw_floor_ceiling(game, x, ray->draw_start, ray->draw_end);
// 		return ;
// 	}
// 	double	wall_x = get_wall_x(game, ray);
// 	int		tex_x = (int)(wall_x * (double)tex->width);

// 	if ((ray->side == 0 && ray->ray_dir_x > 0) \
// 		|| (ray->side == 1 && ray->ray_dir_y > 0))
// 		tex_x = tex->width - tex_x - 1;

// 	double	steps = (double)tex->height / (double)ray->line_height;
// 	double	tex_position = (ray->draw_start - HEIGHT / 2 + ray->line_height / 2) * steps;

// 	draw_floor_ceiling(game, x, ray->draw_start, ray->draw_end);

// 	int		y = ray->draw_start;
// 	while (y <= ray->draw_end && y < HEIGHT)
// 	{
// 		int		tex_y = (int)tex_position;
// 		if (tex_y >= 0 && tex_y < (int)tex->height)
// 		{

// 			uint32_t	color = get_tex_color(tex, tex_x, tex_y);

// 			if (ray->side == 1)
// 			{
// 				uint8_t	r = ((color >> 24) & 0xFF) * 0.75;
// 				uint8_t	g = ((color >> 16) & 0xFF) * 0.75;
// 				uint8_t	b = ((color >> 8) & 0xFF) * 0.75;
// 				uint8_t	a = color & 0xFF;
// 				color = get_rgba_color(r, g, b, a);
// 			}
// 			mlx_put_pixel(game->img, x, y, color);
// 		}
// 		tex_position += steps;
// 		y++;
// 	}
// }
