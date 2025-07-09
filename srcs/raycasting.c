/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpehliva <hpehliva@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 14:34:24 by hpehliva          #+#    #+#             */
/*   Updated: 2025/07/09 10:15:21 by hpehliva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"


void    init_ray(t_game *game, t_ray *ray, int x){
    /*
        - Implement cordinate of camera
        - Calculate the direction of ray cordinate
        - Calculate the distance of DDA(Digital differential analyser)
        - Start to map position and direction of steps 
    */
   // Corrected camera cordinate must be between -[-1,1] distance.
    ray->camera_x = (2 * x)/(double)WIDTH - 1;
    ray->ray_dir_x = game->player.dir_x + game->player.plane_x * ray->camera_x;
    ray->ray_dir_y = game->player.dir_y + game->player.plane_y * ray->camera_x;
    ray->map_x = (int)game->player.x;
    ray->map_y = (int)game->player.y;
    if(ray->ray_dir_x == 0)
    {
        ray->delta_dist_x = 1e30;
    }
    else
    {
        ray->delta_dist_x = fabs(1/ ray->ray_dir_x);// floating-point absolute value function
    }
    if(ray->ray_dir_y == 0)
    {
        ray->delta_dist_y = 1e30;
    }
    else
    {
        ray->delta_dist_y = fabs(1/ ray->ray_dir_y);
    }
    
    // Step directions and initial side distance calculation
    // Ray is going right or left?
    if(ray->ray_dir_x < 0)
    {
        ray->step_x = -1; // it is going to the left
        ray->side_dist_x = (game->player.x - ray->map_x) * ray->delta_dist_x;
    }
    else
    {
        ray->step_x = 1; // It's going to the right
        ray->side_dist_x = (ray->map_x + 1.0 - game->player.x) * ray->delta_dist_x;
    }
    // Ray is going up or down
    if(ray->ray_dir_y < 0)
    {
        ray->step_y = -1; // It's going up
        ray->side_dist_y = (game->player.y - ray->map_y) * ray->delta_dist_y;
    }
    else
    {
        ray->step_y = 1; // it's going down
        ray->side_dist_y = (ray->map_y + 1.0 - game->player.y) * ray->delta_dist_y;
    }
    ray->hit = 0;
}

void perform_dda(t_game *game, t_ray *ray)
{
    while(ray->hit == 0)
    {
        // Choose the nearest grid line
        if(ray->side_dist_x < ray->side_dist_y)
        {
            ray->side_dist_x += ray->delta_dist_x;
            ray->map_x += ray->step_x;
            ray->side = 0; // Vertical
        }
        else
        {
            ray->side_dist_y += ray->delta_dist_y;
            ray->map_y += ray->step_y;
            ray->side = 1; // Horizontal
        }
        // check the wall
        if(game->map.grid[ray->map_y][ray->map_x] == '1')
            ray->hit = 1;
    }
    if(ray->side == 0)
        ray->perp_wall_dist = (ray->map_x - game->player.x +(1-ray->step_x) / 2) / ray->ray_dir_x;
    else
        ray->perp_wall_dist = (ray->map_y - game->player.y +(1-ray->step_y) / 2) / ray->ray_dir_y;
}

void calculate_wall_screen(t_game *game, t_ray *ray){
    /*
        - Calculate the height
        - Draw start/end calculation // TODO
        - Choose textures // TODO
        - Calculate the texture of cordinate // TODO
    */
    ray->line_height = HEIGHT / ray->perp_wall_dist;
    ray->draw_start = -ray->line_height / 2 + HEIGHT / 2; // IT's goin to down
    if(ray->draw_start < 0)
        ray->draw_start = 0;
    ray->draw_end = ray->line_height / 2 + HEIGHT / 2;
    if(ray->draw_end >= HEIGHT)
        ray->draw_end = HEIGHT - 1;
    /*
        HEIGHT = 600
        0 Screen top
        150 ceiling
        300 screen center (HEIGHT / 2)
        450 WALL
        600 screen buttom
        --------------------
        |  Ceiling          |
        |                   |
        ---------------------
        --------------------
        |  WALL             |
        |                   |
        ---------------------
        --------------------
        |  FLOOR.           |
        |                   |
        ---------------------
    */

}

void    raycast(t_game *game)
{
    /*
        For this function
        - Loops for each column of the screen (x = 0 ; x < Width; x++)
        - For each column calculate of ray
        - call the others functions
    */
   int x = 0;
   t_ray ray;
   while(x < WIDTH)
   {
        init_ray(game, &ray, x);
        // Implement the algorithm dda(Digital differential analyzer)
        perform_dda(game, &ray);
        // calculate wall and screean
        calculate_wall_screen(game, &ray);
        // Rendering textures 
        render_textures_wall(); // Julio implemented maybe different name.
        x++;
   }
}
