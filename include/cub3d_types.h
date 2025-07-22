/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_types.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julcalde <julcalde@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 11:50:51 by hpehliva          #+#    #+#             */
/*   Updated: 2025/07/22 20:15:29 by julcalde         ###   ########.fr       */
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
	Color structure to represent RGB colors.
	- r: Red component (0-255)
	- g: Green component (0-255)
	- b: Blue component (0-255)
	- hex: Hexadecimal representation of the color (0xRRGGBB)
*/
typedef struct s_color
{
	unsigned char			r;
	unsigned char			g;
	unsigned char			b;
	unsigned char			hex;
}							t_color;

/*
	Texture structure to hold texture data and its file path.
	- texture: Pointer to the MLX42 texture object.
	- path: File path to the texture image.
*/
typedef struct s_texture
{
	mlx_texture_t			*texture;
	char					*path;
}							t_texture;

/*
	Player structure to hold player information.
	- x: Player X position
	- y: Player Y position
	- dir_x: Player direction X component
	- dir_y: Player direction Y component
	- plane_x: Player camera plane X component
	- plane_y: Player camera plane Y component
	- spawn_dir: Player spawn direction in degrees
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
	Map structure to hold the game map.
	- grid: 2D array representing the map grid
	- width: Width of the map
	- height: Height of the map
*/
typedef struct s_map
{
	char					**grid;
	int						width;
	int						height;
}							t_map;

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
	Garbage collector node structure
*/
typedef struct s_garbco_node
{
	void					*ptr;
	struct s_garbco_node	*next;
}							t_garbco_node;

/*
	Garbage collector structure
*/
typedef struct s_garbco
{
	t_garbco_node			*head;
}							t_garbco;

/*
	Main game structure
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

typedef struct s_square
{
	int						x;
	int						y;
	int						size;
	int						color;
}							t_square;

typedef struct s_draw_data
{
	mlx_texture_t			*tex;
	int						tex_x;
	int						tex_position;
	int						steps;
}							t_draw_data;

#endif