/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpehliva <hpehliva@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 12:05:36 by hpehliva          #+#    #+#             */
/*   Updated: 2025/07/12 12:05:41 by hpehliva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ================================================================== */
/*                            mlx.h                                  */
/*                      (Main umbrella header)                        */
/* ================================================================== */

#ifndef MLX_H
# define MLX_H

# include "../MLX42/include/MLX42/MLX42.h"

/* ===== WINDOW SETTINGS ===== */
# define WIDTH 800
# define HEIGHT 600
# define WIN_TITLE "Cub3D"

/* ===== KEYS ===== */
# define W MLX_KEY_W
# define A MLX_KEY_A
# define S MLX_KEY_S
# define D MLX_KEY_D
# define LEFT MLX_KEY_LEFT
# define RIGHT MLX_KEY_RIGHT
# define KEY_ESC MLX_KEY_ESCAPE
# define KEY_RELEASE MLX_RELEASE
# define KEY_PRESS MLX_PRESS
# define KEY_REPEAT MLX_REPEAT

#endif // MLX_H