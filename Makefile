# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cwannhed <cwannhed@student.42firenze.it>   +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/11/20 16:07:06 by cwannhed          #+#    #+#              #
#    Updated: 2025/11/20 16:07:10 by cwannhed         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3d

SRC = src/main.c		\

CFLAGS = -Wall -Wextra -Werror -g

LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

INCLUDES = -I./includes -I./$(LIBFT_DIR)

all: $(NAME)

$(NAME): $(LIBFT) $(SRC)
	@cc $(SRC) $(INCLUDES) $(CFLAGS) $(LIBFT) -o $(NAME)


$(LIBFT):
	@$(MAKE) --no-print-directory -C $(LIBFT_DIR)

clean:
	@make --no-print-directory -C $(LIBFT_DIR) clean
	@echo "$(YELLOW)Cleaning $(NAME)...$(RESET)"
	@echo "$(RED)Clean completed!$(RESET)"

fclean: clean
	@make --no-print-directory -C $(LIBFT_DIR) fclean
	@echo "$(RED)Removing $(NAME)...$(RESET)"
	@rm -f $(NAME)
	@echo "$(RED)Full clean completed!$(RESET)"

re: fclean all

.PHONY: all clean fclean re

#colors
GREEN = \033[0;32m
BLUE = \033[0;34m
RED = \033[0;31m
YELLOW = \033[0;33m
CYAN = \033[0;36m
RESET = \033[0m
