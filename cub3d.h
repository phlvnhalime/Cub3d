/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpehliva <hpehliva@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 11:49:36 by hpehliva          #+#    #+#             */
/*   Updated: 2025/06/09 11:49:37 by hpehliva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
#define CUB3D_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
# include "MLX42/include/MLX42/MLX42.h"


# define DEBUG 1
#if DEBUG
    # define DEBUG_PRINT(fmt, ...) fprintf(stderr, " [DEBUG] " fmt, ##__VA_ARGS__)
#else
    # define DEBUG_PRINT(fmt, ...) do {} while(0) // Dont do anything when the debug closed
#endif

/* ASCII Color Codes */
# define RST      "\033[0m"
# define RD        "\033[31m"
# define GRN      "\033[32m"
# define YLW     "\033[33m"
# define BLU       "\033[34m"
# define MAGNT    "\033[35m"
# define CYN       "\033[36m"

#define WIDTH 800
#define HEIGHT 600


enum			e_keycode
{
	KEY_UP = 87,
	KEY_DOWN = 83,
	KEY_LEFT = 65,
	KEY_RIGHT = 68,
	RESET = 15,
	ESC = 256,
    RELEASE = 0,
    PRESS = 1,
    REPEAT = 2,

};


typedef struct s_player
{
    mlx_t *mlx;
} t_player;



#endif
