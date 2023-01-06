# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kkleinsc <kkleinsc@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/10 14:21:32 by kkleinsc          #+#    #+#              #
#    Updated: 2023/01/06 15:20:05 by kkleinsc         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc

CFLAGS = -Wall -Wextra -Werror -c

NAME = libft.a

MAND_SRC =	ft_isalpha.c        \
            ft_isdigit.c        \
            ft_isalnum.c        \
            ft_isascii.c        \
            ft_isprint.c        \
            ft_strlen.c         \
            ft_memset.c         \
            ft_bzero.c          \
            ft_memcpy.c         \
            ft_memmove.c        \
            ft_strlcpy.c        \
            ft_strlcat.c        \
            ft_toupper.c        \
            ft_tolower.c        \
            ft_strchr.c         \
            ft_strrchr.c        \
            ft_strncmp.c        \
            ft_memchr.c         \
            ft_memcmp.c         \
            ft_strnstr.c        \
            ft_atoi.c           \
            ft_calloc.c         \
            ft_strdup.c         \
            ft_strjoin.c        \
            ft_substr.c         \
            ft_strtrim.c        \
            ft_split.c          \
            ft_itoa.c           \
            ft_strmapi.c        \
            ft_striteri.c       \
            ft_putchar_fd.c     \
            ft_putstr_fd.c      \
            ft_putendl_fd.c     \
            ft_putnbr_fd.c      \
            ft_printf.c  \
		    output.c	    \
		    tostring.c   \
            get_next_line_bonus.c\
            get_next_line_utils_bonus.c

MAND_OBJ = ${MAND_SRC:.c=.o}

BONUS_SRC =	ft_lstadd_back.c    \
            ft_lstadd_front.c   \
            ft_lstclear.c       \
            ft_lstdelone.c      \
            ft_lstiter.c        \
            ft_lstlast.c        \
            ft_lstmap.c         \
            ft_lstnew.c         \
            ft_lstsize.c

BONUS_OBJ = ${BONUS_SRC:.c=.o}

$(NAME): $(MAND_OBJ)
	@ ar -rc $(NAME) $(MAND_OBJ) 
    
.PHONY: bonus clean fclean re all
all: $(NAME)

%.o: %.c
	@ $(CC) $(CFLAGS) $^

bonus: $(MAND_OBJ) $(BONUS_OBJ)
	@ ar -rc $(NAME) $(MAND_OBJ) $(BONUS_OBJ)

clean:
	@ rm -f $(MAND_OBJ) $(BONUS_OBJ)

fclean: clean
	@ rm -f $(NAME)

re: fclean all