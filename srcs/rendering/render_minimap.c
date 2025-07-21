/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_minimap.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julcalde <julcalde@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 17:28:59 by julcalde          #+#    #+#             */
/*   Updated: 2025/07/21 18:37:47 by julcalde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

// ORIGINAL VERSION of render_minimap function

// void	render_minimap(t_game *game)
// {
// 	t_square	sq;
// 	char		cell;
// 	int			player_cx;
// 	int			player_cy;
// 	int			map_x;
// 	int			map_y;
// 	int			cell_size;
// 	int			offset_x;
// 	int			offset_y;
// 	int			player_radius;

// 	offset_x = 10;
// 	offset_y = 10;
// 	cell_size = 10;
// 	map_y = 0;
// 	while (map_y < game->map.height)
// 	{
// 		map_x = 0;
// 		while (map_x < game->map.width)
// 		{
// 			sq.x = offset_x + map_x * cell_size;
// 			sq.y = offset_y + map_y * cell_size;
// 			sq.size = cell_size;
// 			if (map_x < (int)strlen(game->map.grid[map_y]))
// 			{
// 				cell = game->map.grid[map_y][map_x];
// 				if (cell == '1')
// 					sq.color = MAP_WALL_COLOR;
// 				else if (cell == '0')
// 					sq.color = MAP_FLOOR_COLOR;
// 				else
// 					sq.color = MAP_EMPTY_COLOR;
// 			}
// 			else
// 				sq.color = MAP_EMPTY_COLOR;
// 			draw_square(game, &sq);
// 			map_x++;
// 		}
// 		map_y++;
// 	}
// 	draw_fov_rays(game, offset_x, offset_y, cell_size);
// 	draw_player_collision_area(game, offset_x, offset_y, cell_size);
// 	player_cx = offset_x + (int)(game->player.x * cell_size);
// 	player_cy = offset_y + (int)(game->player.y * cell_size);
// 	draw_player_direction(game, player_cx, player_cy, cell_size);
// 	player_radius = cell_size / 3;
// 	draw_filled_circle(game, player_cx, player_cy, player_radius, PLAYER_COLOR);
// 	mlx_put_pixel(game->img, player_cx, player_cy, 0xFFFFFFFF);
// }

static void	init_minimap_vars(int *offset_x, int *offset_y, int *cell_size)
{
	*offset_x = 10;
	*offset_y = 10;
	*cell_size = 10;
}

static void	draw_map_cell(t_game *game, t_square *sq, char cell)
{
	if (cell == '1')
		sq->color = MAP_WALL_COLOR;
	else if (cell == '0')
		sq->color = MAP_FLOOR_COLOR;
	else
		sq->color = MAP_EMPTY_COLOR;
	draw_square(game, sq);
}

static void	render_map_grid(t_game *game, int offset_x, int offset_y, \
	int cell_size)
{
	t_square	sq;
	int			map_x;
	int			map_y;
	char		cell;

	map_y = 0;
	while (map_y < game->map.height)
	{
		map_x = 0;
		while (map_x < game->map.width)
		{
			sq.x = offset_x + map_x * cell_size;
			sq.y = offset_y + map_y * cell_size;
			sq.size = cell_size;
			if (map_x < (int)strlen(game->map.grid[map_y]))
				cell = game->map.grid[map_y][map_x];
			else
				cell = ' ';
			draw_map_cell(game, &sq, cell);
			map_x++;
		}
		map_y++;
	}
}

static void	render_player_elements(t_game *game, int offset_x, int offset_y, \
	int cell_size)
{
	int	player_cx;
	int	player_cy;
	int	player_radius;

	player_cx = offset_x + (int)(game->player.x * cell_size);
	player_cy = offset_y + (int)(game->player.y * cell_size);
	player_radius = cell_size / 3;
	draw_fov_rays(game, offset_x, offset_y, cell_size);
	draw_player_collision_area(game, offset_x, offset_y, cell_size);
	draw_player_direction(game, player_cx, player_cy, cell_size);
	draw_filled_circle(game, player_cx, player_cy, player_radius);
	mlx_put_pixel(game->img, player_cx, player_cy, 0xFFFFFFFF);
}

void	render_minimap(t_game *game)
{
	int	offset_x;
	int	offset_y;
	int	cell_size;

	init_minimap_vars(&offset_x, &offset_y, &cell_size);
	render_map_grid(game, offset_x, offset_y, cell_size);
	render_player_elements(game, offset_x, offset_y, cell_size);
}
