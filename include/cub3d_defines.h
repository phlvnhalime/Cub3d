/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_defines.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpehliva <hpehliva@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 11:44:58 by hpehliva          #+#    #+#             */
/*   Updated: 2025/07/12 12:01:10 by hpehliva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ================================================================== */
/*                            cub3d_defines.h                         */
/*                      (Main umbrella header)                        */
/* ================================================================== */

#ifndef CUB3D_DEFINES_H
# define CUB3D_DEFINES_H

/*
    Debug Settings
*/

# define DEBUG 1
#if DEBUG
    # define DEBUG_PRINT(fmt, ...) fprintf(stderr, " [DEBUG] " fmt, ##__VA_ARGS__)
#else
    # define DEBUG_PRINT(fmt, ...) do {} while(0)
	Dont do anything when the debug closed
#endif

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

/* 
    Math Constant 
*/
#define PI 3.14159265359f
#define DEG_TO_RAD(deg) ((deg) * (PI / 180.0f))
#define RAD_TO_DEG(rad) ((rad) * (180.0f / PI))
#define FOV 60.0f // Field of view in degrees
#define HALF_FOV (FOV / 2.0f) // Half field of view in degrees

/*
    Speed Settings
*/
#define MOVE_SPEED 0.08 // Adjust for your preferred speed
#define ROT_SPEED 0.045 // Adjust for your preferred rotation speed

#endif