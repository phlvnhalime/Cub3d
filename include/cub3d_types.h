/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_types.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julcalde <julcalde@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 11:50:51 by hpehliva          #+#    #+#             */
/*   Updated: 2025/07/23 00:58:25 by julcalde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ================================================================== */
/*                            cub3d_types.h                           */
/*                      (Main umbrella header)                        */
/* ================================================================== */

#ifndef CUB3D_TYPES_H
# define CUB3D_TYPES_H

# include "../MLX42/include/MLX42/MLX42.h"
# include "mlx.h"

/*
** s_color structure to hold RGB color values.
** - r: Red component of the color (0-255)
** - g: Green component of the color (0-255)
** - b: Blue component of the color (0-255)
** - hex: Hexadecimal representation of the color (not used in this context)
*/
typedef struct s_color
{
	unsigned char			r;
	unsigned char			g;
	unsigned char			b;
	unsigned char			hex;
}							t_color;

/*
** s_texture structure to hold texture information.
** - texture: Pointer to the MLX42 texture object
** - path: Path to the texture file
*/
typedef struct s_texture
{
	mlx_texture_t			*texture;
	char					*path;
}							t_texture;

/*
** s_player structure to hold player information.
** - spawn_char: Character representing the player's spawn point
** - x: X coordinate of the player's position
** - y: Y coordinate of the player's position
** - dir_x: X component of the player's direction vector
** - dir_y: Y component of the player's direction vector
** - plane_x: X component of the player's camera plane vector
** - plane_y: Y component of the player's camera plane vector
** - spawn_dir: Direction the player is facing at spawn (in radians)
*/
typedef struct s_player
{
	char					spawn_char;
	double					x;
	double					y;
	double					dir_x;
	double					dir_y;
	double					plane_x;
	double					plane_y;
	double					spawn_dir;
}							t_player;

/*
** s_map structure to hold the map grid and its dimensions.
** - grid: 2D array of strings representing the map
** - width: Width of the map (number of columns)
** - height: Height of the map (number of rows)
*/
typedef struct s_map
{
	char					**grid;
	int						width;
	int						height;
}							t_map;

/*
** s_ray structure to hold raycasting information.
** - camera_x: X coordinate of the camera in the current column
** - ray_dir_x: X component of the ray direction
** - ray_dir_y: Y component of the ray direction
** - delta_dist_x: Distance to the next vertical grid line
** - delta_dist_y: Distance to the next horizontal grid line
** - side_dist_x: Distance to the next vertical grid line (for side checking)
** - side_dist_y: Distance to the next horizontal grid line (for side checking)
** - perp_wall_dist: Perpendicular distance to the wall hit
** - map_x: X coordinate of the current map cell
** - map_y: Y coordinate of the current map cell
** - step_x: Step direction in the X axis (1 or -1)
** - step_y: Step direction in the Y axis (1 or -1)
** - hit: Hit flag (1 if a wall was hit, 0 otherwise)
** - side: Side flag (0 for vertical hit, 1 for horizontal hit)
** - line_height: Height of the line to be drawn on the screen
** - draw_start: Starting Y coordinate for drawing the line
** - draw_end: Ending Y coordinate for drawing the line
** - x: X coordinate of the current column being processed
*/
typedef struct s_ray
{
	double					camera_x;
	double					ray_dir_x;
	double					ray_dir_y;
	double					delta_dist_x;
	double					delta_dist_y;
	double					side_dist_x;
	double					side_dist_y;
	double					perp_wall_dist;
	int						map_x;
	int						map_y;
	int						step_x;
	int						step_y;
	int						hit;
	int						side;
	int						line_height;
	int						draw_start;
	int						draw_end;
	int						x;
}							t_ray;

/*
** s_garbco_node structure to hold a pointer to a dynamically allocated
** object and a pointer to the next node in the linked list.
** - ptr: Pointer to the dynamically allocated object
** - next: Pointer to the next node in the linked list
*/
typedef struct s_garbco_node
{
	void					*ptr;
	struct s_garbco_node	*next;
}							t_garbco_node;

/*
** s_garbco structure to hold the head of a linked list of
** dynamically allocated objects.
** - head: Pointer to the first node in the linked list
*/
typedef struct s_garbco
{
	t_garbco_node			*head;
}							t_garbco;

/*
** s_game structure to hold the main game state.
** - mlx: Pointer to the MLX42 context
** - img: Pointer to the MLX42 image object for rendering
** - player: Player information
** - map: Map information
** - textures: Array of textures used in the game
** - floor_color: Color of the floor
** - ceiling_color: Color of the ceiling
** - garbco: Garbage collection structure for managing dynamically
**				allocated memory
** - texture_count: Number of textures loaded
** - color_count: Number of colors defined (floor and ceiling)
** - map_started: Flag indicating if the map has started (1) or not (0)
** - map_ended: Flag indicating if the map has ended (1) or not (0)
** - map_valid: Flag indicating if the map is valid (1) or not (0)
** - player_found: Flag indicating if a player has been found in the
** 					map (1) or not (0)
*/
typedef struct s_game
{
	mlx_t					*mlx;
	mlx_image_t				*img;
	t_player				player;
	t_map					map;
	t_texture				textures[4];
	t_color					floor_color;
	t_color					ceiling_color;
	t_garbco				garbco;

	int						texture_count;
	int						color_count;
	int						map_started;
	int						map_ended;
	int						map_valid;
	int						player_found;
}							t_game;

/*
** s_square structure to hold information about a square to be drawn.
** - x: X coordinate of the square's top-left corner
** - y: Y coordinate of the square's top-left corner
** - size: Size of the square (width and height)
** - color: Color of the square (in hexadecimal format)
*/
typedef struct s_square
{
	int						x;
	int						y;
	int						size;
	int						color;
}							t_square;

/*
** s_draw_data structure to hold data for drawing textures.
** - tex: Pointer to the MLX42 texture object to be drawn
** - tex_x: X coordinate of the texture to be drawn
** - tex_position: Position in the texture to start drawing from
** - steps: Number of steps to take when drawing the texture
*/
typedef struct s_draw_data
{
	mlx_texture_t			*tex;
	int						tex_x;
	int						tex_position;
	int						steps;
}							t_draw_data;

#endif