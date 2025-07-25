/* ************************************************************************** */
/*										                                      */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpehliva <hpehliva@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 14:34:24 by hpehliva          #+#    #+#             */
/*   Updated: 2025/07/21 13:15:11 by hpehliva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

/*
** compare_side_dist - Compares the side distances and updates the ray's
** map coordinates and side.
** This function determines which side of the grid the ray is closer to
** and updates the ray's map coordinates accordingly. It also sets the
** side variable to indicate whether the ray hit a vertical or horizontal wall.
**
** @param ray: Pointer to the ray structure containing side distances and
** map coordinates.
*/
static void	compare_side_dist(t_ray *ray)
{
	if (ray->side_dist_x < ray->side_dist_y)
	{
		ray->side_dist_x += ray->delta_dist_x;
		ray->map_x += ray->step_x;
		ray->side = 0;
	}
	else
	{
		ray->side_dist_y += ray->delta_dist_y;
		ray->map_y += ray->step_y;
		ray->side = 1;
	}
}

/*
** perform_dda - Performs the Digital Differential Analyzer (DDA) algorithm
** to find the wall hit.
** This function iterates through the grid based on the ray's direction
** and checks for wall collisions. It updates the ray's hit status and
** calculates the perpendicular wall distance when a wall is hit.
**
** @param game: Pointer to the game structure containing player and map
** information.
** @param ray: Pointer to the ray structure containing ray direction and
** map coordinates.
*/
void	perform_dda(t_game *game, t_ray *ray)
{
	while (ray->hit == 0)
	{
		compare_side_dist(ray);
		if (ray->map_x < 0 || ray->map_x >= game->map.width || ray->map_y < 0
			|| ray->map_y >= game->map.height)
		{
			ray->hit = 1;
			break ;
		}
		if (game->map.grid[ray->map_y]
			&& ray->map_x < (int)ft_strlen(game->map.grid[ray->map_y])
			&& game->map.grid[ray->map_y][ray->map_x] == '1')
			ray->hit = 1;
	}
	if (ray->side == 0)
		ray->perp_wall_dist = (ray->map_x - game->player.x + (1 - ray->step_x)
				/ 2) / ray->ray_dir_x;
	else
		ray->perp_wall_dist = (ray->map_y - game->player.y + (1 - ray->step_y)
				/ 2) / ray->ray_dir_y;
}

/*
** cakculate_wall_screen - Calculates the height and draw start/end
** positions for the wall on the screen.
** This function computes the height of the wall based on the perpendicular
** distance to the wall and sets the start and end positions for drawing
** the wall on the screen. It ensures that the wall is drawn within the
** screen boundaries.
**
** @param ray: Pointer to the ray structure containing the perpendicular
** wall distance and calculated line height.
*/
void	calculate_wall_screen(t_ray *ray)
{
	ray->line_height = (int)(HEIGHT / ray->perp_wall_dist);
	ray->draw_start = -ray->line_height / 2 + HEIGHT / 2;
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	ray->draw_end = ray->line_height / 2 + HEIGHT / 2;
	if (ray->draw_end >= HEIGHT)
		ray->draw_end = HEIGHT - 1;
}

/*
** raycast - Main function for raycasting in the game.
** This function iterates over each pixel in the screen width, initializes
** the ray for that pixel, performs the DDA algorithm to find the wall hit,
** calculates the wall screen position, and renders the wall textures.
**
** @param game: Pointer to the game structure containing player and map
** information.
*/
void	raycast(t_game *game)
{
	int		x;
	t_ray	ray;

	x = 0;
	while (x < WIDTH)
	{
		init_ray(game, &ray, x);
		perform_dda(game, &ray);
		calculate_wall_screen(&ray);
		render_textures_wall(game, &ray, x);
		x++;
	}
}
