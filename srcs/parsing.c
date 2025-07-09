/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpehliva <hpehliva@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 20:35:21 by hpehliva          #+#    #+#             */
/*   Updated: 2025/07/09 14:59:16 by hpehliva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int get_texture_count(char *line)
{
    if(!line)
        return 0; // Null line is not valid
    if(ft_strncmp(line, "NO ", 3) == 0)
        return (0);
    else if(ft_strncmp(line, "SO ", 3) == 0)
        return (1);
    else if(ft_strncmp(line, "WE ", 3) == 0)
        return (2);
    else if(ft_strncmp(line, "EA ", 3) == 0)
        return (3);
    return (-1); // Invalid texture identifier
}

int    parse_texture(t_game *game, char *line)
{
    char *path;
    int i;

    i = get_texture_count(line);
    if(i == -1)
    {
        DEBUG_PRINT("Invalid texture identifier: %s\n", line);
        return (0); // Invalid texture identifier
    }
    path = ft_strtrim(line + 3, " \t\n");
    if (!path || ft_strlen(path) == 0)
    {
        DEBUG_PRINT("Invalid texture path: %s\n", line);
        if(path)
            free(path);
        return (0); // Invalid texture path
    }
     /*
        We can try two methods to assigned the path to the texture:
        1. Directly assign the path to the texture structure.
        2. After loading the texture, assign the path to the texture structure.
    */
    // game->textures[game->texture_count].path = path; // Path to the texture file
    DEBUG_PRINT(CYN"Attempting to load texture: %s\n"RST, path);
    game->textures[i].texture = mlx_load_png(path);
    if (!game->textures[i].texture)
    {
        DEBUG_PRINT("Failed to load texture: %s\n", path);
        // free(path);
        // free(game->textures[game->texture_count].path);
        // game->textures[game->texture_count].path = NULL;
        return (0); // Failed to load texture
    }
    DEBUG_PRINT(GRN"Texture loaded successfully: %s\n"RST, path);
    garbco_add(&game->garbco, path);
    game->textures[i].path = path;
    game->texture_count++;
    DEBUG_PRINT(RD"Texture loaded: %s\n"RST, path);
    DEBUG_PRINT(RD"Texture count: %d\n"RST, game->texture_count);
    if(game->textures[i].texture != NULL)
    {
        DEBUG_PRINT(GRN"Texture %d loaded successfully.\n"RST, i);
    }
    else
    {
        DEBUG_PRINT(RD"Failed to load texture %d.\n"RST, i);
        // free(path); // It must be garbage collector /* TODO */
        return (0); // Failed to load texture
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

void set_color_values(t_game *game, char identifier, int rgb_arr[3])
{
    if (identifier == 'F')
    {
        game->floor_color.r = rgb_arr[0];
        game->floor_color.g = rgb_arr[1];
        game->floor_color.b = rgb_arr[2];
        game->floor_color.hex = (rgb_arr[0] << 16) | (rgb_arr[1] << 8) | rgb_arr[2];
    }
    else if (identifier == 'C')
    {
        game->ceiling_color.r = rgb_arr[0];
        game->ceiling_color.g = rgb_arr[1];
        game->ceiling_color.b = rgb_arr[2];
        game->ceiling_color.hex = (rgb_arr[0] << 16) | (rgb_arr[1] << 8) | rgb_arr[2];
    }
    game->color_count++;
    DEBUG_PRINT(RD"Color set: %c %d,%d,%d\n"RST, identifier, rgb_arr[0], rgb_arr[1], rgb_arr[2]);
    DEBUG_PRINT(RD"Color hex: %x\n"RST, (rgb_arr[0] << 16) | (rgb_arr[1] << 8) | rgb_arr[2]);
    DEBUG_PRINT(GRN"Check color from parsing part is done.\n"RST);

}

int parse_color(t_game *game, char *line)
{
    char **split_line;
    char **rgb;
    int rgb_arr[3];

    if(!is_color_identifier(line))
    {
        DEBUG_PRINT("Invalid color identifier: %s\n", line);
        return (0); // Invalid color identifier
    }
    split_line = ft_split(line, ' ');
    if(!split_line || !split_line[0] || !split_line[1])// This condition must be return true for F
    {
            DEBUG_PRINT("Invalid color format: %s\n", line);
            // free_array(split_line); // It must be garbage collector /* TODO */
            ft_free_split(split_line);
            return (0); // Invalid color format
    }
    rgb = ft_split(split_line[1], ',');
    if(!rgb || ft_arraylen(rgb) != 3)
    {
        DEBUG_PRINT("Invalid RGB format: %s\n", split_line[1]);
        // free_array(rgb); // It must be garbage collector /* TODO */
        ft_free_split(rgb);
        ft_free_split(split_line);
        // free_array(split_line); // It must be garbage collector /* TODO */
        return (0); // Invalid RGB format
    }
    rgb_arr[0] = ft_atoi(rgb[0]);
    rgb_arr[1] = ft_atoi(rgb[1]);
    rgb_arr[2] = ft_atoi(rgb[2]);
    if (!valid_rgb_format(rgb_arr[0], rgb_arr[1], rgb_arr[2]))
    {
        // free_array(rgb); // It must be garbage collector /* TODO */
        ft_free_split(rgb);
        ft_free_split(split_line);
        // free_array(split_line); // It must be garbage collector /* TODO */
        return (0); // Invalid RGB format
    }
    set_color_values(game, split_line[0][0], rgb_arr);
    ft_free_split(rgb);
    ft_free_split(split_line);
   return (1); // Color parsed successfully
}
