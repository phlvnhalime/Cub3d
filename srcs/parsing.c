/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpehliva <hpehliva@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 20:35:21 by hpehliva          #+#    #+#             */
/*   Updated: 2025/07/02 21:17:23 by hpehliva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int    parse_texture(t_game *game, char *line)
{
    char *path;
    if (texture_identifier(line))
    {
        path = ft_strtrim(line + 3, " \t\n");
        if (!path || ft_strlen(path) == 0)
        {
            free(path);
            return (0); // Invalid texture path
        }
        if (game->texture_count < 4)
        {
            game->textures[game->texture_count].path = path;
            game->textures[game->texture_count].texture = mlx_load_png(path);
            if (!game->textures[game->texture_count].texture)
            {
                free(path);
                return (0); // Failed to load texture
            }
            game->texture_count++;
        }
        else
        {
            free(path);
            return (0); // Too many textures
        }
    }
    else
    {
        free(path);
        return (0); // Invalid texture identifier
    }
    return (1); // Texture parsed successfully
}
int valid_rgb_format(int r, int g, int b)
{
    if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
    {
        DEBUG_PRINT("Invalid RGB format: %d, %d, %d\n", r, g, b);
        return (0);
    }
    return (1);
}

void set_color_values(t_game *game, t_color *color, char identifier)
{
    color->r = 0;
    color->g = 0;
    color->b = 0;
    color->hex = 0;
    if (identifier == 'F')
    {
        game->floor_color.r = color->r;
        game->floor_color.g = color->g;
        game->floor_color.b = color->b;
        game->floor_color.hex = (color->r << 16) | (color->g << 8) | color->b;
    }
    else if (identifier == 'C')
    {
        game->ceiling_color.r = color->r;
        game->ceiling_color.g = color->g;
        game->ceiling_color.b = color->b;
        game->ceiling_color.hex = (color->r << 16) | (color->g << 8) | color->b;
    }
    game->color_count++;
    DEBUG_PRINT(RD"Color set: %c %d,%d,%d\n"RST, identifier, color->r, color->g, color->b);
    DEBUG_PRINT(RD"Color hex: %x\n"RST, color->hex);
    DEBUG_PRINT(GRN"Check color from parsing part is done.\n"RST);

}

int parse_color(t_game *game, char *line)
{
   char **split_line;
   char **rgb;
   int r;
   int b;
   int g;
   if(!is_color_identifier(line))
   {
       DEBUG_PRINT("Invalid color identifier: %s\n", line);
       return (0); // Invalid color identifier
   }
   split_line = ft_split(line, ' ');
   if(!split_line || ft_strlen(split_line[0]) < 2)
   {
        DEBUG_PRINT("Invalid color format: %s\n", line);
        // free_array(split_line); // It must be garbage collector /* TODO */
        return (0); // Invalid color format
   }
   rgb = ft_split(split_line[1], ',');
   if(!rgb || ft_arraylen(rgb) != 3)
   {
       DEBUG_PRINT("Invalid RGB format: %s\n", split_line[1]);
       // free_array(rgb); // It must be garbage collector /* TODO */
       // free_array(split_line); // It must be garbage collector /* TODO */
       return (0); // Invalid RGB format
   }
   r = ft_atoi(rgb[0]);
   g = ft_atoi(rgb[1]);
   b = ft_atoi(rgb[2]);
   if (!valid_rgb_format(r, g, b))
   {
       // free_array(rgb); // It must be garbage collector /* TODO */
       // free_array(split_line); // It must be garbage collector /* TODO */
       return (0); // Invalid RGB format
   }
   set_color_values(game, &(game->floor_color), split_line[0][0]);
   return (1); // Color parsed successfully
}
