# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kkleinsc <kkleinsc@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/21 13:18:12 by kkleinsc          #+#    #+#              #
#    Updated: 2023/01/04 14:45:08 by kkleinsc         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc

CFLAGS = -Wall -Wextra -Werror -g

MLXFLAGS = -Lmlx -lmlx -framework OpenGL -framework AppKit

NAME = miniRT

MAIN =	main.c

SRC =	error.c\

TEST =	test/main.c\
		test/template.c\
		test/vector.c\
		test/conversion.c

MATH =	math/vec3d.c\
		math/ray.c\
		math/change_data.c

OBJ = ${SRC:.c=.o}

MOBJ = ${MATH:.c=.o}

MA = ${MAIN:.c=.o}

TOBJ = ${TEST:.c=.o}

.PHONY: all clean fclean re libft bonus test

all: $(NAME)

$(NAME): libft $(OBJ) $(MOBJ) $(MA)
	$(CC) $(CFLAGS) $(OBJ) $(MOBJ) $(MA) -o $(NAME) -L libft -lft $(MLXFLAGS)

test: libft $(OBJ) $(TOBJ) $(MOBJ)
	$(CC) $(CFLAGS) $(OBJ) $(TOBJ) $(MOBJ) -o $(NAME) -L libft -lft
	@ ./$(NAME)
	@ make fclean 

libft:
	@ make -C libft/

clean:
	@ make clean -C libft/
	@ rm -f $(OBJ)

fclean: clean
	@ make fclean -C libft/
	@ rm -f $(NAME)

re: fclean all 