NAME = cub3D

MLX_LINUX = mlx_linux/libmlx.a
MLX_MACOS = mlx_macos/libmlx.a

CC = cc

CFLAGS = -Wall -Wextra -Werror

INCLUDES = -Iincludes

UNAME_S = $(shell uname -s)
ifeq ($(UNAME_S), Linux)
    INCLUDES += -Imlx_linux -Iincludes/linux_include
    LDFLAGS = -Lmlx_linux -lmlx -L/usr/lib -lXext -lX11 -lm -lz
    MLX = $(MLX_LINUX)
else ifeq ($(UNAME_S), Darwin)
    INCLUDES += -Imlx_macos -Iincludes/macos_include
    LDFLAGS = -Lmlx_macos -lmlx -framework OpenGL -framework AppKit
    MLX = $(MLX_MACOS)
else
    $(error Operating system not supported)
endif

SRCS_DIR = srcs
UTILS_DIR = utils
PARSING_DIR = parsing
RENDERING_DIR = rendering
PLAYER_DIR = player

OBJS_DIR = objs

UTILS_SRCS =	$(UTILS_DIR)/ft_putstr_fd.c $(UTILS_DIR)/ft_split.c \
				$(UTILS_DIR)/ft_strcmp.c $(UTILS_DIR)/ft_realloc.c \
				$(UTILS_DIR)/ft_strldup.c $(UTILS_DIR)/ft_strlen.c \
				$(UTILS_DIR)/ft_tablen.c $(UTILS_DIR)/ft_free_tab.c \
				$(UTILS_DIR)/ft_strdel.c $(UTILS_DIR)/ft_rgb_to_int.c \
				$(UTILS_DIR)/get_next_line.c $(UTILS_DIR)/ft_atoi.c \
				$(UTILS_DIR)/ft_print_tab.c $(UTILS_DIR)/ft_memcpy.c \
				$(UTILS_DIR)/ft_distance_to.c

PARSING_SRCS =	$(PARSING_DIR)/scene_reading.c $(PARSING_DIR)/valid_scene_check.c \
				$(PARSING_DIR)/map_reading.c

RENDERING_SRCS =	$(RENDERING_DIR)/render.c $(RENDERING_DIR)/images.c \
					$(RENDERING_DIR)/raycasting_1.c $(RENDERING_DIR)/hand.c \
					$(RENDERING_DIR)/raycasting_2.c $(RENDERING_DIR)/minimap.c

PLAYER_SRCS =	$(PLAYER_DIR)/movement.c $(PLAYER_DIR)/player.c \
				$(PLAYER_DIR)/loop.c $(PLAYER_DIR)/collisions.c

SRCS =	$(addprefix $(SRCS_DIR)/, $(UTILS_SRCS)) \
		$(addprefix $(SRCS_DIR)/, $(PARSING_SRCS)) \
		$(addprefix $(SRCS_DIR)/, $(RENDERING_SRCS)) \
		$(addprefix $(SRCS_DIR)/, $(PLAYER_SRCS)) \
		$(SRCS_DIR)/cub3d.c $(SRCS_DIR)/window_management.c

OBJS = $(SRCS:%.c=$(OBJS_DIR)/%.o)

# ANSI color codes
GREEN = \033[1;32m
YELLOW = \033[1;33m
WHITE = \033[1;97m
BLUE = \033[1;34m
CYAN = \033[1;36m
RED = \033[1;31m
RESET = \033[0m

COL1 = \033[38;2;255;204;153m # Pastel orange
COL2 = \033[38;2;255;214;140m # Light pastel orange
COL3 = \033[38;2;255;224;128m # Pastel yellow-orange
COL4 = \033[38;2;255;234;115m # Pastel orange-yellow
COL5 = \033[38;2;255;244;102m # Light pastel yellow
COL6 = \033[38;2;255;255;153m # Pastel yellow

all: $(MLX) $(NAME)

$(OBJS_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	@echo "$(CYAN)Compiling $<...$(RESET)"
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(MLX_LINUX):
	@echo "$(BLUE)Creating the MLX library...$(RESET)"
	@make -s -C mlx_linux
$(MLX_MACOS):
	@echo "$(BLUE)Creating the MLX library...$(RESET)"
	@make -s -C mlx_macos

$(NAME): $(OBJS)
	@echo "\n$(YELLOW)Linking objects...$(RESET)"
	@$(CC) $(CFLAGS) $(OBJS) $(LDFLAGS) -o $(NAME)
	@echo "$(GREEN)Compilation complete!$(RESET)\n"
	@echo "$(COL1) ██████╗██╗   ██╗██████╗ ██████╗ ██████╗ "
	@echo "$(COL2)██╔════╝██║   ██║██╔══██╗╚════██╗██╔══██╗"
	@echo "$(COL3)██║     ██║   ██║██████╔╝ █████╔╝██║  ██║"
	@echo "$(COL4)██║     ██║   ██║██╔══██╗ ╚═══██╗██║  ██║"
	@echo "$(COL5)╚██████╗╚██████╔╝██████╔╝██████╔╝██████╔╝"
	@echo "$(COL6) ╚═════╝ ╚═════╝ ╚═════╝ ╚═════╝ ╚═════╝ $(RESET)\n"

clean:
	@make -s clean -C mlx_linux
	@make -s clean -C mlx_macos
	@echo "$(RED)Cleaned the MLX library.$(RESET)"
	@rm -rf $(OBJS_DIR)
	@echo "$(RED)Cleaned object files.$(RESET)"

fclean: clean
	@rm -f $(NAME)
	@echo "$(RED)Removed executable.$(RESET)"

re: fclean all

.PHONY: all clean fclean re
