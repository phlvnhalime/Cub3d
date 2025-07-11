.SILENT:

NAME        = cub3D
RM          = rm -f
RM_DIR      = rm -rf

LIBFTDIR    = libft
LIBFT       = $(LIBFTDIR)/libft.a

MLX42_DIR   = MLX42
MLX42_LIB   = $(MLX42_DIR)/build/libmlx42.a

INCLUDE     = -I$(MLX42_DIR)/include -I header -I libft
LDINCLUDE = -L$(MLX42_DIR)/build -lmlx42 -L$(LIBFTDIR) -lft -O3 -L/opt/homebrew/lib -lglfw -framework Cocoa -framework OpenGL -framework IOKit
PERFORMANCE_FLAGS =	-O3 \
					-march=native \
					-mtune=native \
					-flto \
					-ffast-math \
					-funroll-loops \
					-finline-functions \
					-fomit-frame-pointer \
					-fno-stack-protector \
					-DNDEBUG
CFLAGS      = -Wextra -Wall -Werror -g $(INCLUDE)

SRCS = srcs/main.c srcs/parsing.c srcs/init.c \
		srcs/garbage_collector.c srcs/map_parsing.c srcs/utils00_parsing.c \
		srcs/utils01_parsing.c get_next_line/get_next_line.c get_next_line/get_next_line_utils.c \
		srcs/raycasting.c srcs/rendering.c srcs/handle_key.c srcs/input.c

OBJS = $(SRCS:.c=.o)

all:    $(NAME)

# Compile libft
$(LIBFT):
	make -C $(LIBFTDIR) && make clean -C $(LIBFTDIR)

$(MLX42_LIB):
	make -C $(MLX42_DIR)

# Final target to build the executable
$(NAME):    $(MLX42_LIB) $(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LDINCLUDE) $(PERFORMANCE_FLAGS) -o $(NAME)
	echo "\033[1;32m Cub3d and MLX compiled successfully!\033[0m"

# Compile each source file to an object
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean object files
clean:
	$(RM_DIR) $(OBJS)
                                               

# Full clean (also remove MLX42 build directory)
fclean: clean
	$(RM) $(NAME)
	make fclean -C $(LIBFTDIR)
	echo "\033[1;32m All files cleaned successfully!\033[0m"

# Rebuild everything
re: fclean all

.PHONY: all clean fclean re