/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_key.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpehliva <hpehliva@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 08:58:35 by hpehliva          #+#    #+#             */
/*   Updated: 2025/07/09 17:53:02 by hpehliva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"
#include "../include/mlx.h"

void handle_key(mlx_key_data_t keys, void *frame)
{
    t_game *game = (t_game *)frame;
    // First handle it the ESC keys
    if(keys.key == KEY_ESC && keys.action == KEY_PRESS)
    {
        DEBUG_PRINT(RD"The Program is trying to closed\n"RST);
        mlx_close_window(game->mlx);
        return ;
    }

    double move_speed = 0.1;
    double rotation_speed = 0.05;

    if(keys.action == KEY_PRESS || keys.action == KEY_REPEAT)
    {
        // Move to goo
        if(keys.key == W)
        {
            double i;// x
            double j;// y

            i = game->player.x + game->player.dir_x * move_speed;
            j = game->player.y + game->player.dir_y * move_speed;

            if(game->map.grid[(int)j][(int)i] != '1')
            {
                game->player.x = i;
                game->player.y = j;
                DEBUG_PRINT(YLW"Player position_x: %f \n Player position_y: %f \n"RST, i,j);
            }
        }
        else if(keys.key == S)
        {
            // It must be go down
            double i;// x
            double j;// y

            i = game->player.x - game->player.dir_x * move_speed;
            j = game->player.y - game->player.dir_y * move_speed;

            if(game->map.grid[(int)j][(int)i] != '1')
            {
                game->player.x = i;
                game->player.y = j;
                DEBUG_PRINT(YLW"Player position_x: %f \n Player position_y: %f \n"RST, i,j);
            }
        }
        else if(keys.key == A)
        {
            // It must be go left
            double i;// x
            double j;// y

            i = game->player.x - game->player.plane_x * move_speed;
            j = game->player.y - game->player.plane_y * move_speed;

            if(game->map.grid[(int)j][(int)i] != '1')
            {
                game->player.x = i;
                game->player.y = j;
                DEBUG_PRINT(YLW"Player position_x: %f \n Player position_y: %f \n"RST, i,j);
            }
        }
        else if (keys.key == D)
        {
            // It must be go right
            double i;// x
            double j;// y

            i = game->player.x + game->player.plane_x * move_speed;
            j = game->player.y + game->player.plane_y * move_speed;

            if(game->map.grid[(int)j][(int)i] != '1')
            {
                game->player.x = i;
                game->player.y = j;
                DEBUG_PRINT(YLW"Player position_x: %f \n Player position_y: %f \n"RST, i,j);
            }
        }
        else if(keys.key == LEFT)
        {
            double old_i = game->player.dir_x;
            game->player.dir_x = game->player.dir_x * cos(-rotation_speed) - game->player.dir_y * sin(-rotation_speed);
            game->player.dir_y = old_i * sin(-rotation_speed) + game->player.dir_y * cos(-rotation_speed);
            // Camera plane
            double old_plane_i = game->player.plane_x;
            game->player.plane_x = game->player.plane_x * cos(-rotation_speed) - game->player.plane_y * sin(-rotation_speed);
            game->player.plane_y = old_plane_i * sin(-rotation_speed) + game->player.plane_y * cos(-rotation_speed);

        }
         else if(keys.key == RIGHT)
        {
            double old_i = game->player.dir_x;
            game->player.dir_x = game->player.dir_x * cos(rotation_speed) - game->player.dir_y * sin(rotation_speed);
            game->player.dir_y = old_i * sin(rotation_speed) + game->player.dir_y * cos(rotation_speed);
            // Camera plane
            double old_plane_i = game->player.plane_x;
            game->player.plane_x = game->player.plane_x * cos(rotation_speed) - game->player.plane_y * sin(rotation_speed);
            game->player.plane_y = old_plane_i * sin(rotation_speed) + game->player.plane_y * cos(rotation_speed);

        }
    }
}