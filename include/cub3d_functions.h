/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_functions.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpehliva <hpehliva@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 11:50:26 by hpehliva          #+#    #+#             */
/*   Updated: 2025/07/12 15:58:58 by hpehliva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ================================================================== */
/*                            cub3d_functions.c                       */
/*                      (Main umbrella header)                        */
/* ================================================================== */

#ifndef CUB3D_FUNCTIONS_H
# define CUB3D_FUNCTIONS_H

# include "cub3d_types.h"

/* ===== ERROR FUNCTIONS ===== */
void	error_exit(char *msg);
void	error_exit_cleanup(t_game *game, char *msg);
void valid_error(char *content, char *specifier);
void file_error(char *filename, char *error_msg);
void map_errors(char *error_msg, int x, int y);
void texture_error(char *texture_name, char *path, char *error_msg);
void mlx_error(char *function_name);
void malloc_error(void);

/* ===== INITIALIZATION FUNCTIONS ===== */
void	init_data(t_game *data);
void	init_game(t_game *game);

/* ===== PARSING FUNCTIONS ===== */
/* Basic parsing utilities */

int is_empty_line(char *line);
int texture_identifier(char *line);
int is_color_identifier(char *line);
int is_valid_map_character(char c);
void check_color_format(char *line);

/* Texture parsing */
int get_texture_count(char *line);
int parse_texture(t_game *game, char *line);

/* Color parsing */
int valid_rgb_format(int r, int g, int b);
void set_color_values(t_game *game, char identifier, int rgb_arr[3]);
int parse_color(t_game *game, char *line);

/* Map parsing */
int is_map_line(char *line);
int find_player_position(t_game *game);
int check_map_walls(t_game *game);
int parse_map_line(t_game *game, char *line);

/* File parsing */
int parse_file(t_game *game, char *file_path);

/* ===== HELPER FUNCTIONS FOR REFACTORING ===== */
int parse_textures_and_colors(t_game *game, int fd);
int parse_map_section(t_game *game, int fd);
int open_and_validate_file(char *file_path);

/* ===== Garbage collector functions ===== */

void	garbco_add(t_garbco *garbco, void *ptr);
void	garbco_clean(t_garbco *garbco);
void	garbco_remove(t_garbco *garbco, void *ptr);
void	garbco_init(t_garbco *garbco);
void	*garbco_malloc(t_garbco *garbco, size_t size);
void	garbco_game(t_game *game);

/* ===== RAYCASTING FUNCTIONS ===== */
void    raycast(t_game *game);
void    init_ray(t_game *game, t_ray *ray, int x);
void calculate_wall_screen(t_ray *ray);
void perform_dda(t_game *game, t_ray *ray);

/* ===== RENDERING FUNCTIONS ===== */
void    render_textures_wall(t_game *game, t_ray *ray, int x);
void draw_floor_ceiling(t_game *game, int x, int wall_start, int wall_end);
void    draw_vertical_line(t_game *game, int x, int start, int end, uint32_t color);
uint32_t get_tex_color(mlx_texture_t *texture, int tex_x, int tex_y);
uint32_t    get_rgba_color(uint8_t r,uint8_t g, uint8_t b, uint8_t a);
double  get_wall_x(t_game *game, t_ray *ray);
int get_wall_direction(t_ray *ray);

/* ===== INPUT FUNCTIONS ===== */
void handle_key(mlx_key_data_t keys, void *frame); // I need to seperated this as a move_player function and rotation function
void move_player(t_game *game);
void rotate_player(t_game *game);
void input_hook(void *frame);
void setup_hook(t_game *game);
void game_loop(t_game *game);
void	close_window(void *frame);
void	render_frame(void *frame);

/* ===== UTILITY FUNCTIONS ===== */
void	ft_free_split(char **split);

/* ===== VALIDATION FUNCTIONS ===== */
int	validate_args(int ac, char **av);
void valid_map(t_game *game);

#endif