# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ialvarez <ialvarez@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/26 14:41:48 by ialvarez          #+#    #+#              #
#    Updated: 2023/09/27 13:53:03 by ialvarez         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D
CC = gcc
RM = rm -f
MAKE = make
DEBUG = -g3 -fsanitize=address
CFLAGS = -g3 -Wall -Werror -Wextra

# Properties for compiling in MacOS
MLX_LINK = -lmlx -framework OpenGL -framework AppKit

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
