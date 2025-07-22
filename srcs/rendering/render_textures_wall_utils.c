/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_textures_wall_utils.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julcalde <julcalde@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 15:21:40 by julcalde          #+#    #+#             */
/*   Updated: 2025/07/23 00:22:43 by julcalde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

/*
** get_valid_wall_dir - Validates the wall direction for a ray.
** It checks if the wall direction is within the valid range (0 to 3).
**
** @param ray - Pointer to the ray structure containing ray data.
** @return The wall direction if valid, -1 otherwise.
*/
int	get_valid_wall_dir(t_ray *ray)
{
	int	wall_direction;

	wall_direction = get_wall_direction(ray);
	if (wall_direction < 0 || wall_direction >= 4)
		return (-1);
	return (wall_direction);
}

/*
** get_texture - Retrieves the texture for a given wall direction.
** It checks if the texture is valid and returns it.
**
** @param game - Pointer to the game structure containing all necessary data.
** @param wall_direction - The direction of the wall (0: North, 1: East,
** 2: South, 3: West).
** @return Pointer to the texture if valid, NULL otherwise.
*/
mlx_texture_t	*get_texture(t_game *game, int wall_direction)
{
	mlx_texture_t	*tex;

	tex = game->textures[wall_direction].texture;
	if (!tex)
		return (NULL);
	return (tex);
}

/*
** handle_missing_texture - Handles the case when a texture is missing.
** It draws a vertical line with a specific error color and fills the floor
** and ceiling areas with the same color.
**
** @param game - Pointer to the game structure containing all necessary data.
** @param ray - Pointer to the ray structure containing ray data.
** @param x - The x-coordinate of the vertical line to be drawn.
*/
void	handle_missing_texture(t_game *game, t_ray *ray, int x)
{
	uint32_t	error_color;

	error_color = 0xFFFF00FF;
	draw_vertical_line(game, ray->draw_start, ray->draw_end, error_color);
	draw_floor_ceiling(game, x, ray->draw_start, ray->draw_end);
}
