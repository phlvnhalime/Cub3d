/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_textures_wall_utils.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julcalde <julcalde@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 15:21:40 by julcalde          #+#    #+#             */
/*   Updated: 2025/07/22 15:22:03 by julcalde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	get_valid_wall_dir(t_ray *ray)
{
	int	wall_direction;


	wall_direction = get_wall_direction(ray);
	if (wall_direction < 0 || wall_direction >= 4)
		return (-1);
	return (wall_direction);
}

mlx_texture_t	*get_texture(t_game *game, int wall_direction)
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
