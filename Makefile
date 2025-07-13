.SILENT:

# Project Configuration
NAME        = cub3D
CC          = cc
RM          = rm -f
RM_DIR      = rm -rf

# Directories
SRCS_DIR    = srcs
INCLUDE_DIR = include
LIB_DIR     = lib
LIBFT_DIR   = $(LIB_DIR)/libft
GNL_DIR     = $(LIB_DIR)/get_next_line
MLX42_DIR   = MLX42
OBJS_DIR    = objs

# Libraries
LIBFT       = $(LIBFT_DIR)/libft.a
MLX42_LIB   = $(MLX42_DIR)/build/libmlx42.a

# Include paths
INCLUDE     = -I$(MLX42_DIR)/include \
				-I$(INCLUDE_DIR) \
				-I$(LIBFT_DIR) \
				-I$(GNL_DIR)

# Linker flags
LDINCLUDE = -L$(MLX42_DIR)/build -lmlx42\
			-L$(LIBFT_DIR) -lft \
			-lglfw -framework Cocoa -framework OpenGL -framework IOKit \
			# -L/opt/homebrew/lib 

CFLAGS      = -Wextra -Wall -Werror $(INCLUDE)

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
DEBUG_FLAGS = -g -fsanitize=address -O0

# Sources
MAIN_SRCS = $(SRCS_DIR)/main.c

INIT_SRCS = $(SRCS_DIR)/init/init.c

INPUT_SRCS = $(SRCS_DIR)/input/handle_key_mov.c \
			$(SRCS_DIR)/input/handle_key_rot.c \
			$(SRCS_DIR)/input/handle_key.c \
			$(SRCS_DIR)/input/input.c

PARSING_SRCS = $(SRCS_DIR)/parsing/parsing.c \
				$(SRCS_DIR)/parsing/parse_map_01.c \
				$(SRCS_DIR)/parsing/utils00_parsing.c \
				$(SRCS_DIR)/parsing/utils01_parsing.c \
				$(SRCS_DIR)/parsing/parse_map_00.c

RAYCASTING_SRCS = $(SRCS_DIR)/raycasting/raycasting.c

RENDERING_SRCS = $(SRCS_DIR)/rendering/rendering.c \
				$(SRCS_DIR)/rendering/render_utils.c

MEMORY_SRCS = $(SRCS_DIR)/memory/garbage_collector.c \
				$(SRCS_DIR)/memory/garbco_utils.c

ERROR_SRCS = $(SRCS_DIR)/error/error_handling_00.c \
			$(SRCS_DIR)/error/error_handling_01.c

VALIDATION_SRCS = $(SRCS_DIR)/validation/validations.c

GNL_SRCS = $(GNL_DIR)/get_next_line.c \
			$(GNL_DIR)/get_next_line_utils.c

# All sources
SRCS = $(MAIN_SRCS) \
		$(INIT_SRCS) \
		$(INPUT_SRCS) \
		$(PARSING_SRCS) \
		$(RAYCASTING_SRCS) \
		$(RENDERING_SRCS) \
		$(MEMORY_SRCS) \
		$(ERROR_SRCS) \
		$(VALIDATION_SRCS) \
		$(INCLUDE_SRCS)

# Object files
OBJS = $(SRCS:$(SRCS_DIR)/%.c=$(OBJS_DIR)/%.o) \
		$(GNL_SRCS:$(GNL_DIR)/%.c=$(GNL_DIR)/%.o)

# Header files
HEADERS = $(INCLUDE_DIR)/cub3d.h \
			$(INCLUDE_DIR)/cub3d_types.h \
			$(INCLUDE_DIR)/mlx.h

# Default target
all:    $(NAME)

# Create object directories
$(OBJS_DIR):
	mkdir -p $(OBJS_DIR)
	mkdir -p $(OBJS_DIR)/init
	mkdir -p $(OBJS_DIR)/input
	mkdir -p $(OBJS_DIR)/parsing
	mkdir -p $(OBJS_DIR)/raycasting
	mkdir -p $(OBJS_DIR)/rendering
	mkdir -p $(OBJS_DIR)/memory
	mkdir -p $(OBJS_DIR)/error
	mkdir -p $(OBJS_DIR)/validation
	mkdir -p $(OBJS_DIR)/gnl

# Compile libft
$(LIBFT):
	echo "\033[1;32mCompiling libft...\033[0m"
	make -C $(LIBFT_DIR) CFLAGS="-Wall -Wextra -Werror"
	make clean -C $(LIBFT_DIR)

# Compile MLX42
$(MLX42_LIB):
	echo "\033[1;33mCompiling MLX42...\033[0m"
	make -C $(MLX42_DIR)

# Final target to build the executable
$(NAME): $(OBJS_DIR) $(MLX42_LIB) $(LIBFT) $(OBJS)
	echo "\033[1;34mLinking $(NAME)...\033[0m"
	$(CC) $(CFLAGS) $(OBJS) $(LDINCLUDE) $(PERFORMANCE_FLAGS) -o $(NAME)
	echo "\033[1;32m$(NAME) compiled successfully!\033[0m"

# Compile source files to objects (preserve directory structure)
$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

# Compile include directory C files to objects
$(OBJS_DIR)/%.o: $(INCLUDE_DIR)/%.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

# Clean object files
clean:
	echo "\033[1;31mCleaning object files...\033[0m"
	$(RM_DIR) $(OBJS_DIR)
	echo "\033[1;32mObject files cleaned successfully!\033[0m"

# Clean all
fclean: clean
	echo "\033[1;31mCleaning $(NAME)...\033[0m"
	$(RM) $(NAME)
	make fclean -C $(LIBFT_DIR)
	echo "\033[1;32m$(NAME) cleaned successfully!\033[0m"

# Rebuild everything
re: fclean all

# Debug mode
debug: CFLAGS += $(DEBUG_FLAGS)
debug: fclean all
	@echo "Compiled with debug flags: $(DEBUG_FLAGS)"

# Memory leak check
leaks: all
	echo "\033[1;33mRunning leak check...\033[0m"
	leaks --atExit -- ./$(NAME) maps/test.cub

# Valgrind check (if available)
valgrind: all
	echo "\033[1;33mRunning valgrind...\033[0m"
	valgrind --leak-check=full --show-leak-kinds=all ./$(NAME) assets/maps/test.cub

# Display project structure
tree:
	echo "\033[1;34mProject structure:\033[0m"
	tree -I 'obj|*.o|*.a|build' || ls -la

# Display compilation info
info:
	echo "\033[1;34mCompilation info:\033[0m"
	echo "CC: $(CC)"
	echo "CFLAGS: $(CFLAGS)"
	echo "INCLUDE: $(INCLUDE)"
	echo "SRCS: $(words $(SRCS)) source files"
	echo "HEADERS: $(words $(HEADERS)) header files"

# Help target
help:
	echo "\033[1;34mAvailable targets:\033[0m"
	echo "  all         - Build the project (default)"
	echo "  clean       - Remove object files"
	echo "  fclean      - Remove all generated files"
	echo "  re          - Rebuild everything"
	echo "  debug       - Build with debug flags"
	echo "  performance - Build with optimization flags"
	echo "  leaks       - Run with leak detection"
	echo "  valgrind    - Run with valgrind (if available)"
	echo "  tree        - Show project structure"
	echo "  info        - Show compilation information"
	echo "  help        - Show this help"

.PHONY: all clean fclean re debug performance leaks valgrind tree info help