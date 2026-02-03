# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cwannhed <cwannhed@student.42firenze.it    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/02/02 11:35:54 by cwannhed          #+#    #+#              #
#    Updated: 2026/02/03 11:06:11 by cwannhed         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

MAKEFLAGS += --no-print-directory
NAME = cub3D

LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

MLX_DIR = minilibx-linux
MLX_LIBS = -L$(MLX_DIR) -lmlx -lXext -lX11 -lm
MLX_URL = https://github.com/42Paris/minilibx-linux.git

INCLUDES = -I./includes -I./$(LIBFT_DIR)

SRCS	= src/main.c \
	src/parse/basic_parser.c \
	src/parse/cub_parse_utils.c \
	src/parse/cub_parser.c \
	src/parse/map_parser.c \
	src/parse/map_handler.c \
	src/init.c \
	src/cleanup.c \
	src/utils.c \
	src/render/raycast.c \
	src/render/game_loop.c \
	src/render/render.c \
	src/render/raycast_data.c \
	src/render/movements.c \
	src/render/textures.c

BONUS_SRCS = src_bonus/minimap_bonus.c \
	src_bonus/game_loop_bonus.c \
	src_bonus/mouse_events_bonus.c \
	src_bonus/main_bonus.c \
	src_bonus/parse/basic_parser_bonus.c \
	src_bonus/parse/cub_parse_utils_bonus.c \
	src_bonus/parse/cub_parser_bonus.c \
	src_bonus/parse/map_parser_bonus.c \
	src_bonus/parse/map_handler_bonus.c \
	src_bonus/init_bonus.c \
	src_bonus/cleanup_bonus.c \
	src_bonus/utils_bonus.c \
	src_bonus/render/raycast_bonus.c \
	src_bonus/render/render_bonus.c \
	src_bonus/render/raycast_data_bonus.c \
	src_bonus/movements_bonus.c \
	src_bonus/render/textures_bonus.c

CFLAGS = -g -Wall -Werror -Wextra

#	RULES	#

all: mlx_setup $(NAME)

mlx_setup: $(MLX_DIR)/libmlx.a

$(MLX_DIR)/libmlx.a:
	@if [ ! -d "$(MLX_DIR)" ]; then \
		echo "MiniLibX not found. Downloading..."; \
		git clone $(MLX_URL) $(MLX_DIR); \
		echo "MiniLibX downloaded successfully!"; \
	fi
	@echo "Building MiniLibX..."; \
	$(MAKE) -C $(MLX_DIR) --no-print-directory

$(LIBFT):
	@make --no-print-directory -C $(LIBFT_DIR)

$(NAME): $(LIBFT) $(SRCS)
	@cc $(SRCS) $(INCLUDES) $(CFLAGS) $(LIBFT) $(MLX_LIBS) -o $(NAME)
	@$(MAKE) text
	@$(MAKE) luna

bonus: $(LIBFT) $(BONUS_SRCS)
	@cc $(BONUS_SRCS) $(INCLUDES) $(CFLAGS) $(LIBFT) $(MLX_LIBS) -o $(NAME)
	@$(MAKE) text_bonus
	@$(MAKE) luna

clean:
	@make -C $(LIBFT_DIR) clean
	@$(MAKE) txtcln

fclean: clean
	@make  -C $(LIBFT_DIR) fclean
	@rm -f $(NAME)
	@$(MAKE) txtfcln

re: fclean all

.PHONY: all clean fclean re mlx_setup
.SILENT:

text:
	@echo -e '\033[1;95m🌙 In the name of the moon, compile $(NAME) ✨\033[0m'

text_bonus:
	@echo -e '\033[1;95m🌙 In the name of the moon, compile $(NAME) bonus ✨\033[0m'

txtcln:
	@echo -e '\033[1;94mPartially cleaned $(NAME)🧼 \033[0m'

txtfcln:
	@echo -e '\033[1;91mFully cleaned $(NAME)🧽 \033[0m'

luna:
	@echo "\033[38;2;255;255;160m⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣤⣤⣤⣤⣤⣤⣤⣄⣀⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\033[0m"
	@echo "\033[38;2;255;250;165m⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠉⠉⠛⠻⠿⢿⣿⣿⣿⣿⣿⣶⣤⣀⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\033[0m"
	@echo "\033[38;2;255;245;170m⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⠙⠻⣿⣿⣿⣿⣿⣿⣶⣄⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀\033[0m"
	@echo "\033[38;2;255;240;175m⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢸⣿⣷⣤⣀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠙⢿⣿⣿⣿⣿⣿⣿⣦⡀⠀⠀⠀⠀⠀⠀⠀\033[0m"
	@echo "\033[38;2;255;235;180m⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢸⣿⣿⣿⣿⣷⣄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣀⣀⣀⣀⣀⣙⢿⣿⣿⣿⣿⣿⣿⣦⡀⠀⠀⠀⠀⠀\033[0m"
	@echo "\033[38;2;255;230;185m⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢿⣿⣿⣿⣿⣿⣿⣿⣿⣶⣶⣶⣶⣿⣿⣿⣿⣿⣿⣿⣿⣿⠀⠻⣿⣿⣿⣿⣿⣿⣿⣄⠀⠀⠀⠀\033[0m"
	@echo "\033[38;2;255;225;190m⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠘⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠇⠀⠀⢹⣿⣿⣿⣿⣿⣿⣿⣆⠀⠀⠀\033[0m"
	@echo "\033[38;2;255;220;195m⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢠⣿⣿⣿⣿⡟⠹⠿⠟⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡏⠀⠀⠀⠀⢿⣿⣿⣿⣿⣿⣿⣿⡆⠀⠀\033[0m"
	@echo "\033[38;2;255;215;200m⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⡿⠋⡬⢿⣿⣷⣤⣤⣴⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠟⠀⠀⠀⠀⠀⠸⣿⣿⣿⣿⣿⣿⣿⣿⡀⠀\033[0m"
	@echo "\033[38;2;255;210;205m⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠰⡇⢸⡇⢸⣿⣿⣿⠟⠁⢀⣬⢽⣿⣿⣿⣿⣿⣿⠋⠀⠀⠀⠀⠀⠀⠀⣿⣿⣿⣿⣿⣿⣿⣿⣧⠀\033[0m"
	@echo "\033[38;2;255;205;210m⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣼⣧⣈⣛⣿⣿⣿⡇⠀⠀⣾⠁⢀⢻⣿⣿⣿⣿⠇⠀⠀⠀⠀⠀⠀⠀⠀⣿⣿⣿⣿⣿⣿⣿⣿⣿⡀\033[0m"
	@echo "\033[38;2;255;200;215m⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢹⣿⣿⣿⣿⣿⣿⣧⣄⣀⠙⠷⢋⣼⣿⣿⣿⡟⠀⠀⠀⠀⠀⠀⠀⠀⢀⣿⣿⣿⣿⣿⣿⣿⣿⣿⡇\033[0m"
	@echo "\033[38;2;255;195;220m⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠻⣿⣿⣿⣿⣿⣿⣿⣿⣿⣷⣿⣿⣿⣿⡟⠀⠀⠀⠀⠀⠀⠀⠀⠀⢸⣿⣿⣿⣿⣿⣿⣿⣿⣿⡇\033[0m"
	@echo "\033[38;2;255;190;225m⣿⡄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⠙⠻⢿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡟⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠁\033[0m"
	@echo "\033[38;2;255;185;230m⣿⣿⡄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠘⣿⣿⣿⣿⣿⣿⣿⣿⣿⣦⡀⠀⠀⠀⠀⠀⠀⢀⣾⣿⣿⣿⣿⣿⣿⣿⣿⣿⡿⠀\033[0m"
	@echo "\033[38;2;255;180;235m⠸⣿⣿⣄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢰⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣦⡀⠀⠀⠀⢀⣾⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠃⠀\033[0m"
	@echo "\033[38;2;255;175;240m⠀⢹⣿⣿⣧⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢸⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣷⣄⣴⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠏⠀⠀\033[0m"
	@echo "\033[38;2;248;170;240m⠀⠀⠹⣿⣿⣿⣷⣄⠀⠀⠀⠀⠀⠀⠀⠀⣾⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠏⠀⠀⠀\033[0m"
	@echo "\033[38;2;240;165;242m⠀⠀⠀⠙⣿⣿⣿⣿⣿⣶⣤⣀⠀⠀⠀⠀⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠋⠀⠀⠀⠀\033[0m"
	@echo "\033[38;2;235;160;245m⠀⠀⠀⠀⠈⠻⣿⣿⣿⣿⣿⣿⣿⣷⣶⣶⣾⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠟⠁⠀⠀⠀⠀⠀\033[0m"
	@echo "\033[38;2;235;155;250m⠀⠀⠀⠀⠀⠀⠉⠻⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠟⠁⠀⠀⠀⠀⠀⠀⠀\033[0m"
	@echo "\033[38;2;235;150;255m⠀⠀⠀⠀⠀⠀⠀⠀⠈⠛⠿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠿⠋⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀\033[0m"
	@echo "\033[38;2;235;150;255m⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⠙⠻⠿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡿⠿⠛⠉⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\033[0m"
	@echo "\033[38;2;235;150;255m⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⠉⠉⠛⠛⠛⠛⠛⠛⠛⠋⠉⠉⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\033[0m"
