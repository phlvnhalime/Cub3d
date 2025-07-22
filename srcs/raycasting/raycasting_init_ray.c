/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_init_ray.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julcalde <julcalde@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 12:26:25 by julcalde          #+#    #+#             */
/*   Updated: 2025/07/22 23:54:51 by julcalde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

/*
** calculate_delta_dist - Calculates the delta distance for the ray.
** This function computes the distance the ray travels in the x and y
** directions based on the ray's direction vector. If the ray's direction
** component is zero, it assigns a very large value to avoid division by zero.
**
** @param ray: Pointer to the ray structure containing ray direction.
*/
static void	calculate_delta_dist(t_ray *ray)
{
	if (ray->ray_dir_x == 0)
		ray->delta_dist_x = 1e30;
	else
	{
		ray->delta_dist_x = fabs(1 / ray->ray_dir_x);
	}
	if (ray->ray_dir_y == 0)
	{
		ray->delta_dist_y = 1e30;
	}
	else
	{
		ray->delta_dist_y = fabs(1 / ray->ray_dir_y);
	}
}

/*
** calculate_step_and_side_dist_x - Calculates the step direction and side
** distance for the x-coordinate of the ray.
** This function determines whether the ray is moving left or right in the x-axis
** and calculates the corresponding step direction and side distance based on
** the player's position and the ray's direction.
**
** @param game: Pointer to the game structure containing player information.
** @param ray: Pointer to the ray structure containing ray direction and map
** coordinates.
*/
static void	calculate_step_and_side_dist_x(t_game *game, t_ray *ray)
{
	if (ray->ray_dir_x < 0)
	{
		ray->step_x = -1;
		ray->side_dist_x = (game->player.x - ray->map_x) * ray->delta_dist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist_x = (ray->map_x + 1.0 - game->player.x)
			* ray->delta_dist_x;
	}
}

/*
** calculate_step_and_side_dist_y - Calculates the step direction and side
** distance for the y-coordinate of the ray.
** This function determines whether the ray is moving up or down in the y-axis
** and calculates the corresponding step direction and side distance based on
** the player's position and the ray's direction.
**
** @param game: Pointer to the game structure containing player information.
** @param ray: Pointer to the ray structure containing ray direction and map
** coordinates.
*/
static void	calculate_step_and_side_dist_y(t_game *game, t_ray *ray)
{
	if (ray->ray_dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = (game->player.y - ray->map_y) * ray->delta_dist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = (ray->map_y + 1.0 - game->player.y)
			* ray->delta_dist_y;
	}
}

/*
** init_ray - Initializes the ray for the given x-coordinate.
** This function sets the camera position, calculates the ray direction,
** initializes the map coordinates, and calculates the delta distances,
** step directions, and side distances for the ray.
**
** @param game: Pointer to the game structure containing player information.
** @param ray: Pointer to the ray structure to be initialized.
** @param x: The x-coordinate of the ray in the screen space.
*/
void	init_ray(t_game *game, t_ray *ray, int x)
{
	ray->camera_x = (2 * x) / (double)WIDTH - 1;
	ray->ray_dir_x = game->player.dir_x + game->player.plane_x * ray->camera_x;
	ray->ray_dir_y = game->player.dir_y + game->player.plane_y * ray->camera_x;
	ray->map_x = (int)game->player.x;
	ray->map_y = (int)game->player.y;
	calculate_delta_dist(ray);
	calculate_step_and_side_dist_x(game, ray);
	calculate_step_and_side_dist_y(game, ray);
	ray->hit = 0;
}
