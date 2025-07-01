#ifndef MLX_H
#define MLX_H

#include "../MLX42/include/MLX42/MLX42.h"
#include "cub3d.h"

// Define the width and height of the window
#define WIDTH 800
#define HEIGHT 600
#define WIN_TITLE "Cub3D"

/* Map characters */
#define EMPTY '0'
#define WALL '1'
#define PLAYER_N 'N'
#define PLAYER_S 'S'
#define PLAYER_E 'E'
#define PLAYER_W 'W'

/* Move speed */
#define MOVE_SPEED 0.1f
#define ROTATE_SPEED 0.05f

/* Math constant */
#define PI 3.14159265359f
#define DEG_TO_RAD(deg) ((deg) * (PI / 180.0f))
#define RAD_TO_DEG(rad) ((rad) * (180.0f / PI))
#define FOV 60.0f // Field of view in degrees
#define HALF_FOV (FOV / 2.0f) // Half field of view in degrees


// Define the code I can use with shortcuts
#define mlx_texture_t texture_t
#define mlx_image_t image_t
#define mlx_key_data_t key_data_t

// Define the key codes for easier reference
enum e_keycode
{
    KEY_UP = 87,
    KEY_DOWN = 83,
    KEY_LEFT = 65,
    KEY_RIGHT = 68,
    RESET = 15,
    ESC = 256,
    RELEASE = 0,
};




#endif // MLX_H