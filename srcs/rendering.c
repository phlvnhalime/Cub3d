/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpehliva <hpehliva@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 11:52:07 by hpehliva          #+#    #+#             */
/*   Updated: 2025/07/09 15:48:39 by hpehliva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

// Orientation wall
int get_wall_direction(t_ray *ray)
{
    if(ray->side == 0)
    {
        if(ray->ray_dir_x > 0)
            return 3;// east (EA)
        else
            return 2;//west(WE)
    }
    else
    {
        if(ray->ray_dir_y > 0) //south (SO)
            return 1;
        else
            return 0 ;// north (NO)
    }
}

// Calculate textures
double  get_wall_x(t_game *game, t_ray *ray)
{
    double wall_x;
    if(ray->side == 0)
        wall_x = game->player.y + ray->perp_wall_dist * ray->ray_dir_y;
    else
        wall_x = game->player.x + ray->perp_wall_dist * ray->ray_dir_x;
    wall_x = wall_x - floor(wall_x); // Just takes franctional part
    return wall_x;
}

uint32_t    get_rgba_color(uint8_t r,uint8_t g, uint8_t b, uint8_t a){
    return (r << 24) | (g << 16) |(b << 8) | a;
}

uint32_t get_tex_color(mlx_texture_t *texture, int tex_x, int tex_y)
{
    if(!texture || tex_x < 0 || tex_x >= (int)texture->width || tex_y < 0 || tex_y >= (int)texture->height)
        return 0xFF00FFFF;//(RED) // Search it which color you can use! // TODO
    int pix_index = (tex_y * (int)texture->width + tex_x) * texture->bytes_per_pixel;
    uint8_t *pix = texture->pixels;

    uint8_t r = pix[pix_index];
    uint8_t g = pix[pix_index + 1];
    uint8_t b = pix[pix_index+ 2];
    uint8_t a;
    if(texture->bytes_per_pixel == 4)
        a = pix[pix_index+3];
    else
        a = 255;
    return get_rgba_color(r, g, b, a);
}

// Draw vertical
void    draw_vertical_line(t_game *game, int x, int start, int end, uint32_t color)
{
    int y = start;
    while(y <= end && y < HEIGHT)
    {
        if(y >= 0 && x >= 0 && x < WIDTH)
            mlx_put_pixel(game->img, x, y, color);
        y++;
    }
}

// horizontal
void draw_floor_ceiling(t_game *game, int x, int wall_start, int wall_end)
{
    int y;
    uint32_t ceiling_color = get_rgba_color(
        game->ceiling_color.r,
        game->ceiling_color.g,
        game->ceiling_color.b,
        255
    );
    y = 0;
    while(y < wall_start && y < HEIGHT)
    {
        if(x >= 0 && x < WIDTH && y>= 0)
            mlx_put_pixel(game->img, x, y, ceiling_color);
        y++;
    }
    uint32_t floor_color = get_rgba_color(
        game->floor_color.r,
        game->floor_color.g,
        game->floor_color.b,
        255
    );
    y = wall_end + 1;
    while(y < HEIGHT)
    {
        if(x >= 0 && x < WIDTH && y >= 0)
            mlx_put_pixel(game->img, x, y, floor_color);
        y++;
    }
}

void    render_textures_wall(t_game *game, t_ray *ray, int x)
{
    // Determine which wall direction to use
    int wall_direction = get_wall_direction(ray);
    mlx_texture_t *tex = game->textures[wall_direction].texture;
    if(!tex)
    {
        DEBUG_PRINT(RD"Texture is not found: %d"RST, wall_direction);
        return;
    }
    // Calculate the cordinate on the wall
    double wall_x = get_wall_x(game, ray);
    int tex_x = (int)(wall_x * (double)tex->width);
    if((ray->side == 0 && ray->ray_dir_x > 0) ||(ray->side == 1 && ray->ray_dir_y > 0))
        tex_x = tex->width - tex_x -1;
    
    // parameters
    double steps = (double)tex->height / (double)ray->line_height;
    double tex_position = (ray->draw_start - HEIGHT / 2 + ray->line_height / 2) * steps;

    draw_floor_ceiling(game, x, ray->draw_start, ray->draw_end);

    int y = ray->draw_start;
    while(y <= ray->draw_end && y < HEIGHT)
    {
        int tex_y = (int)tex_position;
        if(tex_y >= 0 && tex_y < (int)tex->height)
        {
            uint32_t color = get_tex_color(tex, tex_x, tex_y);
            if(ray->side ==1)
            {
                // darken horizontal walls by %25 
                uint8_t r = ((color >> 24) & 0xFF) * 0.75;
                uint8_t g = ((color >> 16) & 0xFF) * 0.75;
                uint8_t b = ((color >> 8) & 0xFF) * 0.75;
                uint8_t a = color & 0xFF;
                color = get_rgba_color(r, g, b, a);
            }
            mlx_put_pixel(game->img, x, y, color);
        }
        tex_position += steps;
        y++;
    }
}