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
// #define MOVE_SPEED 0.1f
// #define ROTATE_SPEED 0.05f

/* Math constant */
#define PI 3.14159265359f
#define DEG_TO_RAD(deg) ((deg) * (PI / 180.0f))
#define RAD_TO_DEG(rad) ((rad) * (180.0f / PI))
#define FOV 60.0f // Field of view in degrees
#define HALF_FOV (FOV / 2.0f) // Half field of view in degrees


// Define the key codes for easier reference

#define    W MLX_KEY_W
#define    A  MLX_KEY_A
#define    S  MLX_KEY_S
#define    D  MLX_KEY_D
#define    LEFT  MLX_KEY_LEFT
#define    RIGHT  MLX_KEY_RIGHT
#define    KEY_ESC  MLX_KEY_ESCAPE

 #define   KEY_RELEASE  MLX_RELEASE
 #define   KEY_PRESS  MLX_PRESS
 #define   KEY_REPEAT  MLX_REPEAT







#endif // MLX_H