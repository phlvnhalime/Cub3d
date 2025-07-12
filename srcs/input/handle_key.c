/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_key.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpehliva <hpehliva@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 08:58:35 by hpehliva          #+#    #+#             */
/*   Updated: 2025/07/12 14:12:23 by hpehliva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"


void handle_key(mlx_key_data_t keydata, void *frame)
{
    t_game *game = (t_game *)frame;
    // First handle it the ESC keys
    if(keydata.key == KEY_ESC && keydata.action == KEY_PRESS)
    {
        DEBUG_PRINT(RD"The Program is trying to closed\n"RST);
        mlx_close_window(game->mlx);
        return ;
    }
    // raycast(game);
    if(keydata.action == KEY_PRESS || keydata.action == KEY_REPEAT)
    {
        if(keydata.key == W || keydata.key == S || keydata.key == A || keydata.key == D)
        {
            move_player(game);
        }
        if(keydata.key == LEFT || keydata.key == RIGHT)
        {
            rotate_player(game);
        }
    }
}



void rotate_player(t_game *game)
{
    double old_dir_x, old_plane_x;

    // Rotate left
    if (mlx_is_key_down(game->mlx, LEFT))
    {
        old_dir_x = game->player.dir_x;
        game->player.dir_x = game->player.dir_x * cos(-ROT_SPEED) - game->player.dir_y * sin(-ROT_SPEED);
        game->player.dir_y = old_dir_x * sin(-ROT_SPEED) + game->player.dir_y * cos(-ROT_SPEED);

        old_plane_x = game->player.plane_x;
        game->player.plane_x = game->player.plane_x * cos(-ROT_SPEED) - game->player.plane_y * sin(-ROT_SPEED);
        game->player.plane_y = old_plane_x * sin(-ROT_SPEED) + game->player.plane_y * cos(-ROT_SPEED);
    }
    // Rotate right
    if (mlx_is_key_down(game->mlx, RIGHT))
    {
        old_dir_x = game->player.dir_x;
        game->player.dir_x = game->player.dir_x * cos(ROT_SPEED) - game->player.dir_y * sin(ROT_SPEED);
        game->player.dir_y = old_dir_x * sin(ROT_SPEED) + game->player.dir_y * cos(ROT_SPEED);

        old_plane_x = game->player.plane_x;
        game->player.plane_x = game->player.plane_x * cos(ROT_SPEED) - game->player.plane_y * sin(ROT_SPEED);
        game->player.plane_y = old_plane_x * sin(ROT_SPEED) + game->player.plane_y * cos(ROT_SPEED);
    }
}



void move_player(t_game *game)
{
    double new_x, new_y;

    // Forward (W)
    if (mlx_is_key_down(game->mlx, W))
    {
        new_x = game->player.x + game->player.dir_x * MOVE_SPEED;
        new_y = game->player.y + game->player.dir_y * MOVE_SPEED;
        if (game->map.grid[(int)new_y][(int)new_x] != '1')
        {
            game->player.x = new_x;
            game->player.y = new_y;
        }
    }
    // Backward (S)
    if (mlx_is_key_down(game->mlx, S))
    {
        new_x = game->player.x - game->player.dir_x * MOVE_SPEED;
        new_y = game->player.y - game->player.dir_y * MOVE_SPEED;
        if (game->map.grid[(int)new_y][(int)new_x] != '1')
        {
            game->player.x = new_x;
            game->player.y = new_y;
        }
    }
    // Strafe left (A)
    if (mlx_is_key_down(game->mlx, A))
    {
        new_x = game->player.x - game->player.plane_x * MOVE_SPEED;
        new_y = game->player.y - game->player.plane_y * MOVE_SPEED;
        if (game->map.grid[(int)new_y][(int)new_x] != '1')
        {
            game->player.x = new_x;
            game->player.y = new_y;
        }
    }
    // Strafe right (D)
    if (mlx_is_key_down(game->mlx, D))
    {
        new_x = game->player.x + game->player.plane_x * MOVE_SPEED;
        new_y = game->player.y + game->player.plane_y * MOVE_SPEED;
        if (game->map.grid[(int)new_y][(int)new_x] != '1')
        {
            game->player.x = new_x;
            game->player.y = new_y;
        }
    }
}

