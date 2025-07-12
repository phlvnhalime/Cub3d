/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julcalde <julcalde@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 11:49:36 by hpehliva          #+#    #+#             */
/*   Updated: 2025/07/12 14:52:22 by julcalde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../MLX42/include/MLX42/MLX42.h"
# include "../get_next_line/get_next_line.h"
# include "../libft/libft.h"
# include "mlx.h"
# include <errno.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <math.h>

# define DEBUG 1
# if DEBUG
#  define DEBUG_PRINT(fmt, ...) fprintf(stderr, " [DEBUG] " fmt, ##__VA_ARGS__)
# else
    # define DEBUG_PRINT(fmt, ...) do {} while(0)
	Dont do anything when the debug closed
#endif

/* ASCII Color Codes */
# define RST "\033[0m"
# define RD "\033[31m"
# define GRN "\033[32m"
# define YLW "\033[33m"
# define BLU "\033[34m"
# define MAGNT "\033[35m"
# define CYN "\033[36m"

#define MOVE_SPEED 0.08 // Adjust for your preferred speed
#define ROT_SPEED 0.045 // Adjust for your preferred rotation speed

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
}	t_color;

/*
	Texture structure to hold texture data and its file path.
	- texture: Pointer to the MLX42 texture object.
	- path: File path to the texture image.
*/
typedef struct s_texture
{
	mlx_texture_t	*texture;
	char			*path;
}	t_texture;

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
	double	x;         // Player X position
	double	y;         // Player Y position
	double	dir_x;     // Player direction X component
	double	dir_y;     // Player direction Y component
	double	plane_x;   // Player camera plane X component
	double	plane_y;   // Player camera plane Y component
	double	spawn_dir; // Player spawn direction in degrees
	char	spawn_char;  // Character representing the player's spawn direction (N, S, E, W)
}	t_player;

/*
	Map structure to hold the game map.
	- grid: 2D array representing the map grid
	- width: Width of the map
	- height: Height of the map
*/
typedef struct s_map
{
	char	**grid;
	int		width;  // Width of the map
	int		height; // Height of the map
}	t_map;

// Raycasting related structures
/*
	s_ray structure to hold raycasting information.
	This structure is used to store information about the ray being cast in the game.
*/
typedef struct s_ray
{
	double	camera_x;       // Camera X coordinate
	double	ray_dir_x;      // Ray direction X component
	double	ray_dir_y;      // Ray direction Y component
	double	delta_dist_x;   // Distance between grid lines in X direction
	double	delta_dist_y;   // Distance between grid lines in Y direction
	double	side_dist_x;    // Distance to the next vertical grid line
	double	side_dist_y;    // Distance to the next horizontal grid line
	double	perp_wall_dist; // Perpendicular distance to the wall
	int		map_x;             // Current map X coordinate
	int		map_y;             // Current map Y coordinate
	int		step_x;            // Step in X direction (1 or -1)
	int		step_y;            // Step in Y direction (1 or -1)
	int		hit;               // Hit flag (1 if wall hit, 0 otherwise)
	int		side;              // Side of the wall hit (0 for vertical, 1 for horizontal
	int		line_height;       // Height of the wall line to be drawn
	int		draw_start;        // Start of the wall line to be drawn
	int		draw_end;          // End of the wall line to be drawn
}	t_ray;

typedef struct s_garbco_node
{
	void					*ptr;
	struct s_garbco_node	*next;
}	t_garbco_node;

typedef struct s_garbco
{
	t_garbco_node	*head;
}	t_garbco;

typedef struct s_game
{
	mlx_t			*mlx;
	mlx_image_t		*img;
	t_player		player;
	t_map			map;
	t_texture		textures[4]; // Array of textures for walls (N, S, E, W)
	t_color			floor_color;   // Floor color
	t_color			ceiling_color; // Ceiling color
	t_garbco		garbco; // Garbage collector to manage memory
	int				texture_count; // Number of textures loaded
	int				color_count;   // Number of colors loaded
	int				map_started;   // Flag to indicate if the map has started
	int				map_ended;     // Flag to indicate if the map has ended
	int				map_valid;     // Flag to indicate if the map is valid
	int				player_found;  // Flag to indicate if the player position has been found
}	t_game;

/*
	GARBAGE_COLLECTOR00.C
*/

void	garbco_init(t_garbco *garbco);
void	garbco_add(t_garbco *garbco, void *ptr);
void	*garbco_malloc(t_garbco *garbco, size_t size);
void	garbco_remove(t_garbco *garbco, void *ptr);
void	garbco_clean(t_garbco *garbco);

/*
	GARBAGE_COLLECTOR01.C
*/
void	garbco_cleanup_rsrcs(t_game *game);
void	garbco_game(t_game *game);

/*
	HANDLE_KEY.C
*/

void	handle_key(mlx_key_data_t keys, void *frame);
void	rotate_player(t_game *game);
void	rotate_player_left(t_game *game);
void	rotate_player_right(t_game *game);
void	move_player(t_game *game);
void	move_player_front(t_game *game);
void	move_player_back(t_game *game);
void	move_player_left(t_game *game);
void	move_player_right(t_game *game);


/*
	INIT.C
*/

void	init_data(t_game *data);
void	init_game(t_game *game);

/*
	INPUT.C
*/

void	input_hook(void *frame);
void	setup_hook(t_game *game);
void	game_loop(t_game *game);

/* 
	MAP_PARSING.C
*/

int		is_map_line(char *line);
void	set_player_direction(t_game *game, char spawn_char);
int		find_player_position(t_game *game);
int		check_map_walls(t_game *game);// Me
int		parse_map_line(t_game *game, char *line);
void	valid_map(t_game *game);

/*
	PARSING.C
*/

int		get_texture_count(char *line);
int		parse_texture(t_game *game, char *line);
int		valid_rgb_format(int r, int g, int b);
void	set_color_values(t_game *game, char identifier, int rgb_arr[3]);
int		parse_color(t_game *game, char *line);

/*
	RAYCASTING.C
*/

void	init_ray(t_game *game, t_ray *ray, int x);
void	perform_dda(t_game *game, t_ray *ray);
void	calculate_wall_screen(t_ray *ray);
void	raycast(t_game *game);

/*
	RENDERING.C
*/

void		render_textures_wall(t_game *game, t_ray *ray, int x);
void		draw_floor_ceiling(t_game *game, int x, int wall_start, int wall_end);
void		draw_vertical_line(t_game *game, int x, int start, int end, uint32_t color);
uint32_t	get_tex_color(mlx_texture_t *texture, int tex_x, int tex_y);
uint32_t	get_rgba_color(uint8_t r,uint8_t g, uint8_t b, uint8_t a);
double		get_wall_x(t_game *game, t_ray *ray);
int			get_wall_direction(t_ray *ray);

/*
	UTILS00_PARSING.C
*/

int		is_empty_line(char *line);
int		texture_identifier(char *line);
int		is_color_identifier(char *line);
int		is_valid_map_character(char c);
void	check_color_format(char *line);

/*
	UTILS01_PARSING.C
*/

void	ft_free_split(char **split);
int		validate_args(int ac, char **av);
void	error_exit(char *msg);
void	render_frame(void *frame);
void	close_window(void *frame);

/*
	MAIN.C
*/

int		validate_args(int ac, char **av);
void	error_exit(char *msg);
void	render_frame(void *frame);
void	close_window(void *frame);
int		parse_file(t_game *game, char *file);

#endif
