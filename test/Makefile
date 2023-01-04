
CC = gcc

CFLAGS = -Wall -Wextra -Werror -g

MLXFLAGS =  -lft -Lmlx -lmlx -framework OpenGL -framework AppKit

NAME = test

SRC =	main.c\
		template.c\
		vector.c

OBJ = ${SRC:.c=.o}

.PHONY: all clean fclean re libft bonus

all: $(NAME)

$(NAME): libft $(OBJ)
	@ $(CC) $(CFLAGS) $(OBJ) -o $(NAME) ../libft/libft.a

libft:
	@ make -C ../libft/

clean:
	@ make clean -C ../libft/
	@ rm -f $(OBJ)

fclean: clean
	@ make fclean -C ../libft/
	@ rm -f $(NAME)

re: fclean all 