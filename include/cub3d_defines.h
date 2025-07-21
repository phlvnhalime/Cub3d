/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_defines.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpehliva <hpehliva@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 11:44:58 by hpehliva          #+#    #+#             */
/*   Updated: 2025/07/21 14:50:12 by hpehliva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ================================================================== */
/*                            cub3d_defines.h                         */
/*                      (Main umbrella header)                        */
/* ================================================================== */

#ifndef CUB3D_DEFINES_H
# define CUB3D_DEFINES_H

/*
	ASCII Color Codes
*/
# define RST "\033[0m"
# define RD "\033[31m"
# define GRN "\033[32m"
# define YLW "\033[33m"
# define BLU "\033[34m"
# define MAGNT "\033[35m"
# define CYN "\033[36m"

// Colors of the minimap
# define MAP_WALL_COLOR 0x000000FF
# define MAP_FLOOR_COLOR 0xFFFFFFFF
# define MAP_EMPTY_COLOR 0xC0C0C0FF
# define PLAYER_COLOR 0xFF0000FF
# define DIRECTION_COLOR 0x00FF00FF
# define RAY_COLOR 0xFFFF00FF
# define PLAYER_BUFFER_COLOR 0xFF8000FF

/*
	Math Constant
*/
# define PI 3.14159265359f
/*
	Speed Settings
*/
# define MOVE_SPEED 0.08 // Adjust for your preferred speed
# define ROT_SPEED 0.045 // Adjust for your preferred rotation speed

#endif