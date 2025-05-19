.SILENT:

NAME        = cub3d
RM          = rm -f
RM_DIR      = rm -rf

LIBFTDIR    = libft
LIBFT       = $(LIBFTDIR)/libft.a

MLX42_DIR   = MLX42
MLX42_LIB   = $(MLX42_DIR)/build/libmlx42.a

INCLUDE     = -I$(MLX42_DIR)/include -I header -I libft
LDINCLUDE   = -L$(MLX42_DIR)/build -lmlx42 -L$(LIBFTDIR) -lft -lglfw -framework Cocoa -framework OpenGL -framework IOKit
CFLAGS      = -Wextra -Wall -Werror -g $(INCLUDE)

SRCS = main.c \

OBJS = $(SRCS:.c=.o)

all:    $(NAME)

# Compile libft
$(LIBFT):
	make -C $(LIBFTDIR) && make clean -C $(LIBFTDIR)

# Compile ft_printf
$(FT_PRINTF):
	make -C $(FT_PRINTF_DIR) && make clean -C

# Final target to build the executable
$(NAME):    $(MLX42_LIB) $(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LDINCLUDE) -o $(NAME)
	echo "\033[1;32m Cub3D and MLX compiled successfully!\033[0m"

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