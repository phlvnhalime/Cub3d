.SILENT:

# Color and Formatting Variables
RED = \033[31m
GREEN = \033[32m
YELLOW = \033[33m
BLUE = \033[34m
MAGENTA = \033[35m
CYAN = \033[36m
NC = \033[0m
CLEAR_LINE = \033[2K\r

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
MAIN_SRCS = 	$(SRCS_DIR)/main.c

INIT_SRCS = 	$(SRCS_DIR)/init/init.c

INPUT_SRCS =	$(SRCS_DIR)/input/handle_key_mov.c \
				$(SRCS_DIR)/input/handle_key_rot.c \
				$(SRCS_DIR)/input/handle_key.c \
				$(SRCS_DIR)/input/input.c

PARSING_SRCS =	$(SRCS_DIR)/parsing/parsing.c \
				$(SRCS_DIR)/parsing/parse_texture.c \
				$(SRCS_DIR)/parsing/parse_color.c \
				$(SRCS_DIR)/parsing/parse_map_01.c \
				$(SRCS_DIR)/parsing/utils00_parsing.c \
				$(SRCS_DIR)/parsing/utils01_parsing.c \
				$(SRCS_DIR)/parsing/parse_map_02.c \
				$(SRCS_DIR)/parsing/parse_map_00.c \
				$(SRCS_DIR)/parsing/parse_player_pos.c \
				$(SRCS_DIR)/parsing/parse_player_direct.c \
				$(SRCS_DIR)/parsing/parse_color_text.c \
				$(SRCS_DIR)/parsing/utils02_parsing.c \
				$(SRCS_DIR)/parsing/utils03_parsing.c

RAYCASTING_SRCS =	$(SRCS_DIR)/raycasting/raycasting.c \
					$(SRCS_DIR)/raycasting/raycasting_init_ray.c

RENDERING_SRCS =	$(SRCS_DIR)/rendering/rendering.c \
					$(SRCS_DIR)/rendering/draw_fov_rays.c \
					$(SRCS_DIR)/rendering/draw_player_direction.c \
					$(SRCS_DIR)/rendering/draw_player_collision_area.c \
					$(SRCS_DIR)/rendering/draw_filled_circle.c \
					$(SRCS_DIR)/rendering/render_minimap.c \
					$(SRCS_DIR)/rendering/render_textures_wall.c \
					$(SRCS_DIR)/rendering/render_textures_wall_utils.c \
					$(SRCS_DIR)/rendering/render_utils.c

MEMORY_SRCS =	$(SRCS_DIR)/memory/garbage_collector.c \
				$(SRCS_DIR)/memory/garbco_utils.c

ERROR_SRCS =	$(SRCS_DIR)/error/error_handling_00.c \
				$(SRCS_DIR)/error/error_handling_01.c

VALIDATION_SRCS =	$(SRCS_DIR)/validation/validations.c

GNL_SRCS =	$(GNL_DIR)/get_next_line.c \
			$(GNL_DIR)/get_next_line_utils.c

# All sources
SRCS =	$(MAIN_SRCS) \
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

# Track compilation progress
TOTAL_SRCS = $(words $(SRCS) $(GNL_SRCS))
CURRENT = 0

# Default target
all:    $(NAME)

# Create object directories
$(OBJS_DIR):
	@mkdir -p $(OBJS_DIR)
	@mkdir -p $(OBJS_DIR)/init
	@mkdir -p $(OBJS_DIR)/input
	@mkdir -p $(OBJS_DIR)/parsing
	@mkdir -p $(OBJS_DIR)/raycasting
	@mkdir -p $(OBJS_DIR)/rendering
	@mkdir -p $(OBJS_DIR)/memory
	@mkdir -p $(OBJS_DIR)/error
	@mkdir -p $(OBJS_DIR)/validation
	@mkdir -p $(OBJS_DIR)/gnl

# Compile libft
$(LIBFT):
	@echo "$(YELLOW)🚧 Building LIBFT 🚧$(NC)"
	@make -C $(LIBFT_DIR) CFLAGS="-Wall -Wextra -Werror"
	@make clean -C $(LIBFT_DIR)
	@echo "$(GREEN)✅ LIBFT Compiled ✅$(NC)"

# Always build MLX42 when running make
MLX42:
	@echo "$(YELLOW)🚧 Building MLX42 🚧$(NC)"
	@cd $(MLX42_DIR) && cmake -B build > /dev/null 2>&1
	@cd $(MLX42_DIR) && cmake --build build -j4 > /dev/null 2>&1 || (echo "$(RED)Failed to build MLX42$(NC)" && exit 1)
	@echo "$(GREEN)✅ MLX42 Compiled ✅$(NC)"

# Compile source files to objects (preserve directory structure)
$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c $(HEADERS)
	@$(eval CURRENT := $(shell echo $$(($(CURRENT) + 1))))
	@$(eval PERCENT := $(shell echo $$(($(CURRENT) * 100 / $(TOTAL_SRCS)))))
	@printf "$(CLEAR_LINE)$(YELLOW)🚧 Building Cub3D $(PERCENT)%% [$(CURRENT)/$(TOTAL_SRCS)] $(CYAN)$<$(NC) 🚧"
	@$(CC) $(CFLAGS) -c $< -o $@

# Compile GNL source files to objects
$(GNL_DIR)/%.o: $(GNL_DIR)/%.c $(HEADERS)
	@$(eval CURRENT := $(shell echo $$(($(CURRENT) + 1))))
	@$(eval PERCENT := $(shell echo $$(($(CURRENT) * 100 / $(TOTAL_SRCS)))))
	@printf "$(CLEAR_LINE)$(YELLOW)🚧 Building GNL $(PERCENT)%% [$(CURRENT)/$(TOTAL_SRCS)] $(CYAN)$<$(NC) 🚧"
	@$(CC) $(CFLAGS) -c $< -o $@

# Final target to build the executable
$(NAME): $(OBJS_DIR) MLX42 $(LIBFT) $(OBJS)
	@echo "$(CLEAR_LINE)$(YELLOW)🚧 Building $(NAME) 🚧$(NC)"
	@$(CC) $(CFLAGS) $(OBJS) $(LDINCLUDE) $(PERFORMANCE_FLAGS) -o $(NAME)
	@echo "$(CLEAR_LINE)$(GREEN)✅ Done Compiling ✅$(NC)\n"
	@echo
	@echo "\033[38;2;0;102;255m		██╗    ██╗███████╗██╗      ██████╗ ██████╗ ███╗   ███╗███████╗    ████████╗ ██████╗         \033[0m";
	@echo "\033[38;2;0;102;255m		██║    ██║██╔════╝██║     ██╔════╝██╔═══██╗████╗ ████║██╔════╝    ╚══██╔══╝██╔═══██╗        \033[0m";
	@echo "\033[38;2;0;102;255m		██║ █╗ ██║█████╗  ██║     ██║     ██║   ██║██╔████╔██║█████╗         ██║   ██║   ██║        \033[0m";
	@echo "\033[38;2;0;102;255m		██║███╗██║██╔══╝  ██║     ██║     ██║   ██║██║╚██╔╝██║██╔══╝         ██║   ██║   ██║        \033[0m";
	@echo "\033[38;2;0;102;255m		╚███╔███╔╝███████╗███████╗╚██████╗╚██████╔╝██║ ╚═╝ ██║███████╗       ██║   ╚██████╔╝        \033[0m";
	@echo "\033[38;2;0;102;255m		 ╚══╝╚══╝ ╚══════╝╚══════╝ ╚═════╝ ╚═════╝ ╚═╝     ╚═╝╚══════╝       ╚═╝    ╚═════╝         \033[0m";
	@echo "\033[38;2;0;102;255m 	                                                                                              \033[0m";
	@echo "\033[38;2;0;102;255m          	                ██████╗██╗   ██╗██████╗         ██████╗ ██████╗                            \033[0m";
	@echo "\033[38;2;0;102;255m          	               ██╔════╝██║   ██║██╔══██╗        ╚════██╗██╔══██╗                           \033[0m";
	@echo "\033[38;2;0;102;255m          	               ██║     ██║   ██║██████╔╝         █████╔╝██║  ██║                           \033[0m";
	@echo "\033[38;2;0;102;255m          	               ██║     ██║   ██║██╔══██╗         ╚═══██╗██║  ██║                           \033[0m";
	@echo "\033[38;2;0;102;255m          	               ╚██████╗╚██████╔╝██████╔╝        ██████╔╝██████╔╝                           \033[0m";
	@echo "\033[38;2;0;102;255m          	                ╚═════╝ ╚═════╝ ╚═════╝         ╚═════╝ ╚═════╝                            \033[0m";
	@echo "\033[38;2;0;102;255m                                                                                                        \033[0m";
	@echo "\033[38;2;94;13;148m▖  ▖  ▜            ▗     ▄▖  ▌ ▄▖▄         ▄▖▄                    ▜       ▗ ▘                               ▌  ▌                 ▗ ▘    ▌\033[0m";
	@echo "\033[38;2;94;13;148m▌▞▖▌█▌▐ ▛▘▛▌▛▛▌█▌  ▜▘▛▌  ▌ ▌▌▛▌▄▌▌▌    ▀▌  ▄▌▌▌  ▛▛▌▀▌▀▌█▌  █▌▚▘▛▌▐ ▛▌▛▘▀▌▜▘▌▛▌▛▌  ▛▌▀▌▛▛▌█▌  ▛▌▛▌▌▌▌█▌▛▘█▌▛▌  ▛▌▌▌  ▛▘▀▌▌▌▛▘▀▌▛▘▜▘▌▛▌▛▌▌\033[0m";
	@echo "\033[38;2;94;13;148m▛ ▝▌▙▖▐▖▙▖▙▌▌▌▌▙▖  ▐▖▙▌  ▙▖▙▌▙▌▄▌▙▘▗   █▌  ▄▌▙▘  ▌▌▌█▌▙▖▙▖  ▙▖▞▖▙▌▐▖▙▌▌ █▌▐▖▌▙▌▌▌  ▙▌█▌▌▌▌▙▖  ▙▌▙▌▚▚▘▙▖▌ ▙▖▙▌  ▙▌▙▌  ▌ █▌▙▌▙▖█▌▄▌▐▖▌▌▌▙▌▖\033[0m";
	@echo "\033[38;2;94;13;148m                                   ▘                            ▌                  ▄▌         ▌                  ▄▌      ▄▌           ▄▌ \033[0m";
	@echo "\033[38;2;94;13;148m▖ ▖    ▘    ▗             ▗         ▗   ▜                   ▘▗ ▌   ▗     ▗        ▌       ▜ ▜         ▘      ▖  ▖▘  ▘▖ ▘▌ ▖▖             \033[0m";
	@echo "\033[38;2;94;13;148m▛▖▌▀▌▌▌▌▛▌▀▌▜▘█▌  ▀▌  ▛▘█▌▜▘▛▘▛▌▄▖▛▘▜▘▌▌▐ █▌  ▛▛▌▀▌▀▌█▌  ▌▌▌▌▜▘▛▌  ▜▘█▌▚▘▜▘▌▌▛▘█▌▛▌  ▌▌▌▀▌▐ ▐ ▛▘  ▌▌▛▘▌▛▌▛▌  ▛▖▞▌▌▛▌▌▌ ▌▛▌▚▘             \033[0m";
	@echo "\033[38;2;94;13;148m▌▝▌█▌▚▘▌▙▌█▌▐▖▙▖  █▌  ▌ ▙▖▐▖▌ ▙▌  ▄▌▐▖▙▌▐▖▙▖  ▌▌▌█▌▙▖▙▖  ▚▚▘▌▐▖▌▌  ▐▖▙▖▞▖▐▖▙▌▌ ▙▖▙▌  ▚▚▘█▌▐▖▐▖▄▌  ▙▌▄▌▌▌▌▙▌  ▌▝ ▌▌▌▌▌▙▖▌▙▌▌▌▗            \033[0m";
	@echo "\033[38;2;94;13;148m        ▄▌                            ▄▌                                                                 ▄▌                              \033[0m";
	@echo "\033[38;2;94;13;148m▄▖    ▜                             ▌      ▗   ▗     ▘         ▌         ▘    ▐▘▘    ▗                       ▘             ▗ ▌           \033[0m";
	@echo "\033[38;2;94;13;148m▙▖▚▘▛▌▐ ▛▌▛▘█▌    ▛▛▌▛▌▌▌█▌    ▀▌▛▌▛▌  ▛▘▛▌▜▘▀▌▜▘█▌  ▌▛▌  ▀▌  ▛▌▌▌▛▌▀▌▛▛▌▌▛▘  ▜▘▌▛▘▛▘▜▘▄▖▛▌█▌▛▘▛▘▛▌▛▌  █▌▛▌▌▌▌▛▘▛▌▛▌▛▛▌█▌▛▌▜▘▌           \033[0m";
	@echo "\033[38;2;94;13;148m▙▖▞▖▙▌▐▖▙▌▌ ▙▖▗   ▌▌▌▙▌▚▘▙▖▗   █▌▌▌▙▌  ▌ ▙▌▐▖█▌▐▖▙▖  ▌▌▌  █▌  ▙▌▙▌▌▌█▌▌▌▌▌▙▖  ▐ ▌▌ ▄▌▐▖  ▙▌▙▖▌ ▄▌▙▌▌▌  ▙▌▌▌▚▘▌▌ ▙▌▌▌▌▌▌▙▖▌▌▐▖▖           \033[0m";
	@echo "\033[38;2;94;13;148m    ▌         ▘            ▘                                    ▄▌                       ▌                                               \033[0m";
	@echo
	@echo "\033[38;2;0;153;255m\nPlayer Controls:\033[0m"
	@echo "\033[38;2;0;153;255m- W: Move forward\033[0m"
	@echo "\033[38;2;0;153;255m- A: Move leftward\033[0m"
	@echo "\033[38;2;0;153;255m- S: Move backward\033[0m"
	@echo "\033[38;2;0;153;255m- D: Move rightward\033[0m"
	@echo "\033[38;2;0;153;255m- Left Arrow: Rotate camera left\033[0m"
	@echo "\033[38;2;0;153;255m- Right Arrow: Rotate camera right\033[0m"
	@echo "\033[38;2;0;153;255m\n\nTo start type:\n./cub3D <map_name.cub>\033[0m"

# Clean object files
clean:
	@echo "$(YELLOW)🚧 Cleaning 🚧$(NC)"
	@sleep 0.15
	@printf "$(RED)🧹 Cleaning in Progress 🧹$(NC)\n"
	@sleep 0.15
	@printf "$(YELLOW)🛁 Scrubbing Code 🛁$(NC)\n"
	@sleep 0.15
	@printf "$(CYAN)🧽 Polishing Project 🧽$(NC)\n"
	@sleep 0.15
	@printf "$(MAGENTA)🧴 Tidying Up 🧴$(NC)\n"
	@sleep 0.15
	@printf "$(GREEN)✅ Done Cleaning ✅$(NC)\n"
	@$(RM_DIR) $(OBJS_DIR)

# Clean all
fclean: clean
	@echo "$(YELLOW)🚧 Cleaning $(NAME) 🚧$(NC)"
	@sleep 0.15
	@printf "$(RED)🧹 Cleaning in Progress 🧹$(NC)\n"
	@sleep 0.15
	@printf "$(YELLOW)🛁 Scrubbing Code 🛁$(NC)\n"
	@sleep 0.15
	@printf "$(CYAN)🧽 Polishing Project 🧽$(NC)\n"
	@sleep 0.15
	@printf "$(MAGENTA)🧴 Tidying Up 🧴$(NC)\n"
	@sleep 0.15
	@printf "$(GREEN)✅ Done Cleaning ✅$(NC)\n\n"
	@$(RM) $(NAME)
	@$(RM_DIR) $(MLX42_DIR)/build
	@make fclean -C $(LIBFT_DIR)

# Rebuild everything
re: fclean all

# Display project structure
tree:
	@echo "\033[1;34mProject structure:\033[0m"
	@tree -I 'obj|*.o|*.a|build' || ls -la

# Display compilation info
info:
	@echo "\033[1;34mCompilation info:\033[0m"
	@echo "CC: $(CC)"
	@echo "CFLAGS: $(CFLAGS)"
	@echo "INCLUDE: $(INCLUDE)"
	@echo "SRCS: $(words $(SRCS)) source files"
	@echo "HEADERS: $(words $(HEADERS)) header files"

# Help target
help:
	@echo "\033[1;34mAvailable targets:\033[0m"
	@echo "  all         - Build the project (default)"
	@echo "  clean       - Remove object files"
	@echo "  fclean      - Remove all generated files"
	@echo "  re          - Rebuild everything"
	@echo "  performance - Build with optimization flags"
	@echo "  tree        - Show project structure"
	@echo "  info        - Show compilation information"
	@echo "  help        - Show this help"

.PHONY: all clean fclean re debug performance leaks valgrind tree info help MLX42