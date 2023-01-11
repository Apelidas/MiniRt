# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pooneh <pooneh@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/21 13:18:12 by kkleinsc          #+#    #+#              #
#    Updated: 2023/01/11 23:41:18 by pooneh           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


CFLAGS = -Wall -Wextra -Werror -g -fsanitize=address

MLXFLAGS = -Lmlx -lmlx -framework OpenGL -framework AppKit

NAME = miniRT

SRC_DIR = src

MAIN =	$(SRC_DIR)/main.c

SRC =	$(SRC_DIR)/error.c\
		$(SRC_DIR)/parser.c\
		$(SRC_DIR)/parser_utils.c\
		$(SRC_DIR)/parser_camera.c\
		$(SRC_DIR)/parser_light.c\
		$(SRC_DIR)/parser_plane.c\
		$(SRC_DIR)/parser_sphere.c\
		$(SRC_DIR)/parser_cylinder.c\

TEST =	test/main.c\
		test/template.c\
		test/vec3d_len.c\
		test/vec3d_norm.c\
		test/vec3d_cross.c\
		test/vec3d_equal.c\
		test/vec3d_cpy.c\
		test/ray_cpy.c\
		test/ray_onray.c\
		test/ray_equal.c\
		test/conversion.c

MATH =	math/vec3d.c\
		math/ray.c\
		math/ray_util.c\
		math/change_data.c\
		math/vec3d_util.c

OBJ = ${SRC:.c=.o}

MOBJ = ${MATH:.c=.o}

MA = ${MAIN:.c=.o}

TOBJ = ${TEST:.c=.o}

.PHONY: all clean fclean re libft bonus test norm

all: $(NAME)

$(NAME): libft $(OBJ) $(MOBJ) $(MA)
	@$(CC) $(CFLAGS) $(OBJ) $(MOBJ) $(MA) -o $(NAME) -L libft -lft $(MLXFLAGS)

%.o : %.c
	@$(CC) $(CFLAGS) -c $^ -o $@

test: libft $(OBJ) $(TOBJ) $(MOBJ)
	@$(CC) $(CFLAGS) $(OBJ) $(TOBJ) $(MOBJ) -o $(NAME) -L libft -lft
	@ ./$(NAME)
	@ make fclean

norm:
	echo "\033c"
	echo "\nROOT:\n"
	norminette *.c *.h || true
	echo "\nMATH:\n"
	norminette math/ || true
	echo "\nSRC:\n"
	norminette src/ || true

libft:
	@ make -C libft/

clean:
	@ make clean -C libft/
	@ rm -f $(OBJ) $(MOBJ) $(MA) $(TOBJ)

fclean: clean
	@ make fclean -C libft/
	@ rm -f $(NAME)

re: fclean all 