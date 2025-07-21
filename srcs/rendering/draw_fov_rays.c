/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_fov_rays.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julcalde <julcalde@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 18:00:57 by julcalde          #+#    #+#             */
/*   Updated: 2025/07/21 18:03:27 by julcalde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

// ORIGINAL VERSION of draw_fov_rays function

// void	draw_fov_rays(t_game *game, int offset_x, int offset_y,
	// 		int cell_size)
	// {
	// 	double	base_angle;
	// 	double	angle;
	// 	double	dx;
	// 	double	dy;
	// 	double	x;
	// 	double	y;
	// 	int		map_x;
	// 	int		map_y;
	// 	int		draw_x;
	// 	int		draw_y;
	// 	int		num_rays;
	// 	double	fov;
	// 	double	step;
	// 	int		max_steps;
	// 	int		r;
	// 	int		i;

	// 	num_rays = 10;
	// 	fov = M_PI / 3;
	// 	base_angle = atan2(game->player.dir_y, game->player.dir_x);
	// 	step = 0.05;
	// 	max_steps = (int)(3.0 / step);
	// 	r = 0;
	// 	while (r < num_rays)
	// 	{
	// 		angle = base_angle + fov * ((double)r / (num_rays - 1) - 0.5);
	// 		dx = cos(angle);
	// 		dy = sin(angle);
	// 		x = game->player.x;
	// 		y = game->player.y;
	// 		i = 0;
	// 		while (i < max_steps)
	// 		{
	// 			map_x = (int)x;
	// 			map_y = (int)y;
	// 			if (map_x < 0 || map_x >= game->map.width || map_y < 0
	// 				|| map_y >= game->map.height)
	// 				break ;
	// 			if (map_x < (int)strlen(game->map.grid[map_y])
	// 				&& game->map.grid[map_y][map_x] == '1')
	// 				break ;
	// 			draw_x = offset_x + (int)(x * cell_size);
	// 			draw_y = offset_y + (int)(y * cell_size);
	// 			if (draw_x >= 0 && draw_x < WIDTH && draw_y >= 0 
	//				 && draw_y < HEIGHT)
	// 				mlx_put_pixel(game->img, draw_x, draw_y, RAY_COLOR);
	// 			x += dx * step;
	// 			y += dy * step;
	// 			i++;
	// 		}
	// 		r++;
	// 	}
	// }	

static void	init_ray_params(t_game *game, double *base_angle, int *num_rays, \
	double *fov)
{
	*num_rays = 10;
	*fov = M_PI / 3;
	*base_angle = atan2(game->player.dir_y, game->player.dir_x);
}

static void	calculate_ray_step(double angle, double step, double *dx, \
	double *dy)
{
	*dx = cos(angle) * step;
	*dy = sin(angle) * step;
}

static void	draw_single_ray(t_game *game, int offset_x, int offset_y, \
	double *ray_data)
{
	int		draw_x;
	int		draw_y;
	int		map_x;
	int		map_y;
	int		i;

	i = 0;
	while (i < (int)(3.0 / ray_data[0]))
	{
		map_x = (int)ray_data[1];
		map_y = (int)ray_data[2];
		if (map_x < 0 || map_x >= game->map.width || map_y < 0 \
			|| map_y >= game->map.height)
			break ;
		if (map_x < (int)strlen(game->map.grid[map_y]) \
		&& game->map.grid[map_y][map_x] == '1')
			break ;
		draw_x = offset_x + (int)(ray_data[1] * ray_data[3]);
		draw_y = offset_y + (int)(ray_data[2] * ray_data[3]);
		if (draw_x >= 0 && draw_x < WIDTH && draw_y >= 0 && draw_y < HEIGHT)
			mlx_put_pixel(game->img, draw_x, draw_y, RAY_COLOR);
		ray_data[1] += ray_data[4];
		ray_data[2] += ray_data[5];
		i++;
	}
}

void	draw_fov_rays(t_game *game, int offset_x, int offset_y, int cell_size)
{
	double	ray_data[6];
	double	base_angle;
	double	fov;
	int		num_rays;
	int		r;

	init_ray_params(game, &base_angle, &num_rays, &fov);
	ray_data[0] = 0.05;
	ray_data[3] = (double)cell_size;
	r = 0;
	while (r < num_rays)
	{
		ray_data[1] = game->player.x;
		ray_data[2] = game->player.y;
		calculate_ray_step(base_angle + fov * ((double)r / (num_rays - 1) \
		- 0.5), ray_data[0], &ray_data[4], &ray_data[5]);
		draw_single_ray(game, offset_x, offset_y, ray_data);
		r++;
	}
}
