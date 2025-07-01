/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpehliva <hpehliva@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 11:49:36 by hpehliva          #+#    #+#             */
/*   Updated: 2025/07/01 15:08:07 by hpehliva         ###   ########.fr       */
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
#include "../MLX42/include/MLX42/MLX42.h"
#include "../libft/libft.h"
#include "mlx.h"
#include "../get_next_line/get_next_line.h"

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

// Define the code I can use with shortcuts
#define mlx_texture_t texture_t
#define mlx_key_data_t key_data_t


typedef struct s_player
{
    /*Player directories*/
    
} t_player;


typedef struct s_game
{
    mlx_t *mlx;
    mlx_image_t *img;
    t_player player;

} t_game;



#endif
