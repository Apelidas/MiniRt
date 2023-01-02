# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kkleinsc <kkleinsc@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/21 13:18:12 by kkleinsc          #+#    #+#              #
#    Updated: 2023/01/02 17:43:24 by kkleinsc         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc

CFLAGS = -Wall -Wextra -Werror -g

MLXFLAGS =  -lft -Lmlx -lmlx -framework OpenGL -framework AppKit

NAME = miniRT

SRC =	main.c

OBJ = ${SRC:.c=.o}

.PHONY: all clean fclean re libft bonus test

all: $(NAME)

$(NAME): libft $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME) -L libft $(MLXFLAGS)

test:
	make -C test/
	@ ./test/test
	@ make fclean -C test/

libft:
	@ make -C libft/

clean:
	@ make clean -C libft/
	@ rm -f $(OBJ)

fclean: clean
	@ make fclean -C libft/
	@ rm -f $(NAME)

re: fclean all 