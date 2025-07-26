/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_minimap.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julcalde <julcalde@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 17:28:59 by julcalde          #+#    #+#             */
/*   Updated: 2025/07/26 13:26:33 by julcalde         ###   ########.fr       */
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

/*
** init_minimap_vars - Initializes the variables for the minimap.
** It sets the offsets for the minimap and the size of each cell.
**
** @param offset_x - Pointer to the x offset for the minimap.
** @param offset_y - Pointer to the y offset for the minimap.
** @param cell_size - Pointer to the size of each cell in the minimap grid.
*/
static void	init_minimap_vars(int *offset_x, int *offset_y, int *cell_size)
{
	*offset_x = 10;
	*offset_y = 10;
	*cell_size = 7;
}

/*
** draw_map_cell - Draws a single cell of the map on the minimap.
** It determines the color of the cell based on its type:
** wall ('1'), floor ('0'), or empty space (other characters).
**
** @param game - Pointer to the game structure containing all necessary data.
** @param sq - Pointer to the square structure representing the cell.
** @param cell - The character representing the cell type ('1', '0', or other).
*/
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

/*
** render_map_grid - Renders the grid of the map on the minimap.
** It iterates through each cell of the map, calculates its position,
** and draws the corresponding square based on the cell type.
**
** @param game - Pointer to the game structure containing all necessary data.
** @param offset_x - The x offset for the minimap.
** @param offset_y - The y offset for the minimap.
** @param cell_size - The size of each cell in the minimap grid.
*/
static void	render_map_grid(t_game *game, int offset_x, int offset_y,
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

/*
** render_player_elements - Renders the player elements on the minimap.
** It calculates the player's center coordinates, draws the field of view rays,
** collision area, player direction, and the player position as a filled circle.
**
** @param game - Pointer to the game structure containing all necessary data.
** @param offset_x - The x offset for the minimap.
** @param offset_y - The y offset for the minimap.
** @param cell_size - The size of each cell in the minimap grid.
*/
static void	render_player_elements(t_game *game, int offset_x, int offset_y,
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

/*
** render_minimap - Renders the minimap for the game.
** It initializes the minimap variables, renders the map grid,
** and draws the player elements such as the field of view rays,
** collision area, direction, and player position.
**
** @param game - Pointer to the game structure containing all necessary data.
*/
void	render_minimap(t_game *game)
{
	int	offset_x;
	int	offset_y;
	int	cell_size;

	init_minimap_vars(&offset_x, &offset_y, &cell_size);
	render_map_grid(game, offset_x, offset_y, cell_size);
	render_player_elements(game, offset_x, offset_y, cell_size);
}
