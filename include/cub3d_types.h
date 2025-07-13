/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_types.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpehliva <hpehliva@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 11:50:51 by hpehliva          #+#    #+#             */
/*   Updated: 2025/07/12 12:02:59 by hpehliva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ================================================================== */
/*                            cub3d_types.h                           */
/*                      (Main umbrella header)                        */
/* ================================================================== */

#ifndef CUB3D_TYPES_H
# define CUB3D_TYPES_H

# include "mlx.h"
# include "../MLX42/include/MLX42/MLX42.h"

/*
	Color structure to represent RGB colors.
	- r: Red component (0-255)
	- g: Green component (0-255)
	- b: Blue component (0-255)
	- hex: Hexadecimal representation of the color (0xRRGGBB)
*/
typedef struct s_color
{
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;
	unsigned char	hex;
}					t_color;

/*
	Texture structure to hold texture data and its file path.
	- texture: Pointer to the MLX42 texture object.
	- path: File path to the texture image.
*/
typedef struct s_texture
{
	mlx_texture_t	*texture;
	char			*path;
}					t_texture;

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
	/*Player directories*/
	double x;         // Player X position
	double y;         // Player Y position
	double dir_x;     // Player direction X component
	double dir_y;     // Player direction Y component
	double plane_x;   // Player camera plane X component
	double plane_y;   // Player camera plane Y component
	double spawn_dir; // Player spawn direction in degrees
	char spawn_char;  // Character representing the player's spawn direction (N, S, E, W)
}					t_player;

/*
	Map structure to hold the game map.
	- grid: 2D array representing the map grid
	- width: Width of the map
	- height: Height of the map
*/
typedef struct s_map
{
	char			**grid;
	int width;  // Width of the map
	int height; // Height of the map
}					t_map;

// Raycasting related structures
/*
	s_ray structure to hold raycasting information.
	This structure is used to store information about the ray being cast in the game.
*/
typedef struct s_ray
{
	double camera_x;       // Camera X coordinate
	double ray_dir_x;      // Ray direction X component
	double ray_dir_y;      // Ray direction Y component
	double delta_dist_x;   // Distance between grid lines in X direction
	double delta_dist_y;   // Distance between grid lines in Y direction
	double side_dist_x;    // Distance to the next vertical grid line
	double side_dist_y;    // Distance to the next horizontal grid line
	double perp_wall_dist; // Perpendicular distance to the wall
	int map_x;             // Current map X coordinate
	int map_y;             // Current map Y coordinate
	int step_x;            // Step in X direction (1 or -1)
	int step_y;            // Step in Y direction (1 or -1)
	int hit;               // Hit flag (1 if wall hit, 0 otherwise)
	int side;              // Side of the wall hit (0 for vertical, 1 for horizontal
	int line_height;       // Height of the wall line to be drawn
	int draw_start;        // Start of the wall line to be drawn
	int draw_end;          // End of the wall line to be drawn
}					t_ray;

/*
	Garbage collector node structure
*/
typedef struct s_garbco_node
{
	void *ptr;
	struct s_garbco_node *next;
} t_garbco_node;

/*
	Garbage collector structure
*/
typedef struct s_garbco
{
	t_garbco_node *head;
} t_garbco;

/*
    Main game structure
*/
typedef struct s_game
{
	mlx_t			*mlx;
	mlx_image_t		*img;
	t_player		player;
	t_map			map;
	t_texture textures[4]; // Array of textures for walls (N, S, E, W)
	t_color floor_color;   // Floor color
	t_color ceiling_color; // Ceiling color
	t_garbco		garbco; // Garbage collector to manage memory

	int texture_count; // Number of textures loaded
	int color_count;   // Number of colors loaded
	int map_started;   // Flag to indicate if the map has started
	int map_ended;     // Flag to indicate if the map has ended
	int map_valid;     // Flag to indicate if the map is valid
	int player_found;  // Flag to indicate if the player position has been found
}					t_game;

#endif