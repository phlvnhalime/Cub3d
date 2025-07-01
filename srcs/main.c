/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpehliva <hpehliva@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 11:49:13 by hpehliva          #+#    #+#             */
/*   Updated: 2025/07/01 21:42:00 by hpehliva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

/*
    * Arguments:
    -  a map format .cub
    * External Functs:
    -  open, close, read, write,
    printf, malloc, free, perror,
    strerror, exit
    - All functions of the math library (-lm man man 3 math)
     It means:
            - libm library!
            #include <math.h> and compile it with -lm 
            

    - All function of the Minilibx

    * (?) The management of your window must remain smooth: changing to another win-
dow, minimizing, etc.
    * (?) Display different wall textures (the choice is yours) that vary depending on which
side the wall is facing (North, South, East, West).
    * (?) Your program must be able to set the floor and ceiling colors to two different ones.
    * (?) The left and right arrow keys of the keyboard must allow you to look left and
    right in the maze.
    ◦The W, A, S, and D keys must allow you to move the point of view through
    the maze.
    ◦Pressing ESC must close the window and quit the program cleanly.
    ◦Clicking on the red cross on the window’s frame must close the window and
    quit the program cleanly.
    ◦The use of images of the minilibX is strongly recommended.

    ** Map **
    - ◦The map must be composed of only 6 possible characters: 0 for an empty space,
    1 for a wall, and N,S,E or W for the player’s start position and spawning
    orientation.
    This is a simple valid map:
    111111
    100101
    101001
    1100N1
    111111
    ◦The map must be closed/surrounded by walls, if not the program must return
    an error.
    ◦Except for the map content, each type of element can be separated by one or
    more empty line(s).
    ◦Except for the map content which always has to be the last, each type of
    element can be set in any order in the file.
    ◦Except for the map, each type of information from an element can be separated
    by one or more space(s).
    ◦The map must be parsed as it looks in the file. Spaces are a valid part of the
    map and are up to you to handle. You must be able to parse any kind of map,
    as long as it respects the rules of the map.
    7
    cub3D My first RayCaster with miniLibX
    ◦Each element (except the map) firsts information is the type identifier (com-
    posed by one or two character(s)), followed by all specific informations for each
    object in a strict order such as :
    ∗ North texture:
    NO ./path_to_the_north_texture
    · identifier: NO
    · path to the north texure
    ∗ South texture:
    SO ./path_to_the_south_texture
    · identifier: SO
    · path to the south texure
    ∗ West texture:
    WE ./path_to_the_west_texture
    · identifier: WE
    · path to the west texure
    ∗ East texture:
    EA ./path_to_the_east_texture
    · identifier: EA
    · path to the east texure
    ∗ Floor color:
    F 220,100,0
    · identifier: F
    · R,G,B colors in range [0,255]: 0, 255, 255
    * Ceiling color:
    C 225,30,0
    · identifier: C
    · R,G,B colors in range [0,255]: 0, 255, 255
    ** EXAMPLE **
        NO ./path_to_the_north_texture
        SO ./path_to_the_south_texture
        WE ./path_to_the_west_texture
        EA ./path_to_the_east_texture
        F 220,100,0
        C 225,30,0
        1111111111111111111111111
        1000000000110000000000001
        1011000001110000000000001   
        1001000000000000000000001
        111111111011000001110000000000001
        100000000011000001110111111111111
        11110111111111011100000010001
        11110111111111011101010010001
        11000000110101011100000010001
        10000000000000001100000010001
        10000000000000001101010010001
        11000001110101011111011110N0111
        11110111 1110101 101111010001
        11111111 1111111 111111111111
    ◦If any misconfiguration of any kind is encountered in the file, the program
    must exit properly and return "Error\n" followed by an explicit error message
    of your choice.
    


*/

// // Simple key handler function
// void key_handler(mlx_key_data_t keydata, void* param)
// {
//     mlx_t* mlx = (mlx_t*)param;
    
//     // Close window when ESC is pressed
//     if (keydata.key == ESC && keydata.action == PRESS)
//     {
//         mlx_close_window(mlx);
//     }
// }


// // Close handler for the red X button
// void close_handler(void* param)
// {
//     mlx_t* mlx = (mlx_t*)param;
//     mlx_close_window(mlx);
// }


// int main(void)
// {
//     //initialized MLX42
//     mlx_t *mlx = mlx_init(WIDTH, HEIGHT, "Simple wolfenstein 3D", true);
//     if(!mlx)
//     {
//         fprintf(stderr, "Error: Failed to initialized MLX42\n");
//         return (EXIT_FAILURE);
//     }
//     // Create a simple image to display
//     mlx_image_t *img = mlx_new_image(mlx, 300, 300);
//     if(!img)
//     {
//         fprintf(stderr, "Error: Failed to create image\n");
//         mlx_terminate(mlx);
//         return (EXIT_FAILURE);
//     }
//     // Fill the image with a red colour (RGBA!)
//     for(uint32_t y = 0; y < img->height; y++)
//     {
//         for(uint32_t x = 0;  x < img->width; x++)
//             mlx_put_pixel(img, x, y,0xFF0000FF); // Red
        
//     }
//     // Position of the images
//     if(mlx_image_to_window(mlx, img, 300, 300) < 0)
//     {
//         fprintf(stderr, "Error: Failed to display image\n");
//         mlx_delete_image(mlx, img);
//         mlx_terminate(mlx);
//         return (EXIT_FAILURE);
//     }

//     // Set up event handlers
//     mlx_key_hook(mlx, key_handler, mlx);        // Handle key presses
//     mlx_close_hook(mlx, close_handler, mlx);    // Handle window close

//     // Start the main loop (this will block until window is closed)
//     mlx_loop(mlx);

//     // Clean up
//     mlx_delete_image(mlx, img);
//     mlx_terminate(mlx);

//     return (EXIT_SUCCESS);
// }

int validate_args(int ac, char **av)
{
    int len;

    if(ac != 2)
    {
        printf("Usage: %s <map_file.cub>\n", av[0]);
        return (0);
    }
    len = strlen(av[1]);
    if(len < 5 || strcmp(av[1] + len - 4, ".cub") != 0)
    {
        printf("Error: Map file must have '.cub' \n");
        return (0);
    }
    return (1);
    
}

void error_exit(char *msg)
{
    fprintf(stderr, "Error\n %s\n",msg); // changed this func.
    exit(EXIT_FAILURE);
}

int parse_file(t_game *game, char file)
{
    int fd;
    char *line;
    int nbr_element;

    nbr_element = 0;
    fd = open(&file, O_RDONLY);
    if(fd < 0)
        return 0;
    while((line = get_next_line(fd)) && nbr_element < 6)
    {
        if(line[0] == '\n')
        {
            free(line);
            continue;
        }
        //TODO Add textures and colors and increase elements.
        free(line);
        
    }
    if(nbr_element != 6)
        return (close(fd),0);
    // TODO Add map for parsing part
    
    close(fd);
    return (1);
}
/*Start again*/

int main(int ac, char **av)
{
    t_player game;
    if(!validate_args(ac,av))
        return (EXIT_FAILURE);

    /*TODO*/
    // Initialized game:
    
    /*Parse arguments and set up game*/
    if(!parse_file(&game, *av[1]))
    {
        error_exit("Failed to parse .cub file");
    }
}