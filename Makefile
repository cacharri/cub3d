# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ialvarez <ialvarez@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/26 14:41:48 by ialvarez          #+#    #+#              #
#    Updated: 2023/09/26 19:12:01 by ialvarez         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D
CC = gcc
RM = rm -f
MAKE = make
DEBUG = -g3 -fsanitize=address
CFLAGS = -g3 -Wall -Werror -Wextra $(KEYCODES_CFLAGS)

# Properties for compiling in MacOS
MLX_LINK = -lmlx -framework OpenGL -framework AppKit
ESC = KEY_ESC=53
W = KEY_W=13
A = KEY_A=0
S = KEY_S=1
D = KEY_D=2
UP = KEY_UP=126
DOWN = KEY_DOWN=125
LEFT = KEY_LEFT=123
RIGHT = KEY_RIGHT=124

KEYCODES_CFLAGS = -D $(ESC) -D $(W) -D $(A) -D $(S) -D $(D) -D $(UP) -D $(DOWN) -D $(LEFT) -D $(RIGHT)

# COLORS #
GREEN = \033[0;32m
YELLOW = \033[0;33m
GREY = \033[2;37m
MAGENTA = \033[0;35m
NO_COLOR = \033[0m

# SOURCES & OBJECTS #
SRCS =	

OBJS = $(SRCS:.c=.o)

# RULES #
all: $(NAME)

$(NAME): $(OBJS)
	@$(MAKE) -s all -C libft
	@$(CC) $(CFLAGS) $(OBJS) $(MLX_LINK) libft/libft.a -o $(NAME)
	@echo "$(GREY) Cub3d compiled $(GREEN) ✔✔ $(NO_COLOR)"

test: all
	@echo "$(YELLOW) Running test of Cub3d $(NO_COLOR)"
	@read -p "Select map number: " map; \
	./cub3D maps/map0$${map}.cub

clean:
	@clear
	@$(RM) $(OBJS)
	@$(MAKE) clean -C libft
	@echo "$(MAGENTA) Cleaned $(NO_COLOR)"

fclean: clean
	@$(RM) $(NAME)
	@$(RM) libft/libft.a
	@echo "$(MAGENTA) Cub3d cleaned $(NO_COLOR)"

re: fclean all

.PHONY: all re clean fclean
