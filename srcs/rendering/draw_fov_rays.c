/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_fov_rays.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julcalde <julcalde@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 18:00:57 by julcalde          #+#    #+#             */
/*   Updated: 2025/07/23 00:02:49 by julcalde         ###   ########.fr       */
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

/*
** init_ray_params - Initializes parameters for raycasting.
** This function sets the number of rays, field of view (FOV),
** and base angle for the rays based on the player's direction.
**
** @param game: Pointer to the game structure containing player data.
** @param base_angle: Pointer to store the base angle of the rays.
** @param num_rays: Pointer to store the number of rays to be cast.
** @param fov: Pointer to store the field of view in radians.
*/
static void	init_ray_params(t_game *game, double *base_angle, int *num_rays, \
	double *fov)
{
	*num_rays = 10;
	*fov = M_PI / 3;
	*base_angle = atan2(game->player.dir_y, game->player.dir_x);
}

/*
** calculate_ray_step - Calculates the step size for a ray based on its angle.
** This function computes the change in x and y coordinates for a ray
** given its angle and step size. It uses trigonometric functions to
** determine the direction of the ray.
**
** @param angle: The angle of the ray in radians.
** @param step: The step size for the ray.
** @param dx: Pointer to store the change in x coordinate.
** @param dy: Pointer to store the change in y coordinate.
*/
static void	calculate_ray_step(double angle, double step, double *dx, \
	double *dy)
{
	*dx = cos(angle) * step;
	*dy = sin(angle) * step;
}

/*
** draw_single_ray - Draws a single ray in the game.
** This function calculates the path of a ray based on the provided
** ray data, which includes the ray's step size and direction.
** It iterates through the ray's path until it hits a wall or reaches
** the maximum distance, drawing the ray on the game image.
**
** @param game: Pointer to the game structure containing player and map data.
** @param offset_x: Horizontal offset for drawing the ray.
** @param offset_y: Vertical offset for drawing the ray.
** @param ray_data: Array containing ray data:
**                  - ray_data[0]: Step size for the ray.
**                  - ray_data[1]: Current x position of the ray.
**                  - ray_data[2]: Current y position of the ray.
**                  - ray_data[3]: Scale factor for drawing the ray.
**                  - ray_data[4]: Step increment in x direction.
**                  - ray_data[5]: Step increment in y direction.
*/
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

/*
** draw_fov_rays - Draws rays in the field of view of the player.
** This function calculates the angles for the rays based on the player's
** direction and field of view, then iterates through each ray to
** calculate its path until it hits a wall or reaches the maximum distance.
** It draws each ray on the game image.
**
** @param game: Pointer to the game structure containing player and map data.
** @param offset_x: Horizontal offset for drawing the rays.
** @param offset_y: Vertical offset for drawing the rays.
** @param cell_size: Size of each cell in the map, used for scaling the rays.
*/
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
