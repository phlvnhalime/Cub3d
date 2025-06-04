#ifndef CUB3D_H
# define CUB3D_H

# include <errno.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include "MLX42/include/MLX42/MLX42.h"
# include "libft/libft.h"
# include "get_next_line/get_next_line.h"


# define DEBUG 1
#if DEBUG
    # define DEBUG_PRINT(fmt, ...) fprintf(stderr, " [DEBUG] " fmt, ##__VA_ARGS__)
#else
    # define DEBUG_PRINT(fmt, ...) do {} while(0) // Dont do anything when the debug closed
#endif

/* ----- ASCII Color Codes ----- */

# define RESET      "\033[0m"
# define BLACK      "\033[30m"
# define RED        "\033[31m"
# define GREEN      "\033[32m"
# define YELLOW     "\033[33m"
# define BLUE       "\033[34m"
# define MAGENTA    "\033[35m"
# define CYAN       "\033[36m"

/* ----- Structs ----- */

typedef struct s_texture
{
	void	*image;
	void	*data;
	int		width;
	int		heigth;
	int		bpp;
	int		size_line;
	int		endian;
}	t_texture;

typedef struct s_map
{
	char	**grid;
	int		width;
	int		heigth;
	char	*no_texture_path;
	char	*so_texture_path;
	char	*we_texture_path;
	char	*ea_texture_path;
	int		floor_color;
	int		ceiling_color;
}	t_map;

typedef struct s_vector
{
	double	x;
	double	y;
}	t_vector;

typedef struct s_ray
{
	t_vector	pos;
	t_vector	dir;
	t_vector	delta_dist;
	t_vector	side_dist;
	t_vector	step;
	int			hit;
	int			side;
	int			map_x;
	int			map_y;
	double		perp_wall_dist;
} t_ray;

typedef struct s_player
{
	t_vector	pos;
	t_vector	dir;
	t_vector	plane;
}	t_player;

typedef struct s_game
{
    void		*mlx;
    void		*window;
    void		*image;
    void		*image_data;
    int			bpp;
    int			size_line;
    int			endian;
    t_player	player;
	t_map		map;
	t_texture	textures[4];
	int			keys[256];
}	t_game;

/* ----- Functions ----- */

void	ft_error_exit(char *msg);
void	verify_args(int argc, char *argv);

#endif