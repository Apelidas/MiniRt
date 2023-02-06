CFLAGS = -Wall -Wextra -Werror -g 
#-fsanitize=address

MLXFLAGS = -Lmlx -lmlx -framework OpenGL -framework AppKit

NAME = miniRT

SRC_DIR = src

SRC_MATH = math/

SRC_TEST = test/

MAIN =	$(SRC_DIR)/main.c

SRC =	$(SRC_DIR)/error.c\
		$(SRC_DIR)/debug.c\
		$(SRC_DIR)/color.c\
		$(SRC_DIR)/color_util.c\
		$(SRC_DIR)/parser.c\
		$(SRC_DIR)/parser_utils.c\
		$(SRC_DIR)/parser_camera.c\
		$(SRC_DIR)/parser_light.c\
		$(SRC_DIR)/parser_plane.c\
		$(SRC_DIR)/parser_sphere.c\
		$(SRC_DIR)/parser_cylinder.c\
		$(SRC_DIR)/mlx_utils.c\
		$(SRC_DIR)/projection.c\
		$(SRC_DIR)/ray.c\
		$(SRC_DIR)/intersection.c\
		$(SRC_DIR)/color_calculation.c

TEST =	$(SRC_TEST)main.c\
		$(SRC_TEST)template.c\
		$(SRC_TEST)vec3d_len.c\
		$(SRC_TEST)vec3d_norm.c\
		$(SRC_TEST)vec3d_cross.c\
		$(SRC_TEST)vec3d_equal.c\
		$(SRC_TEST)vec3d_cpy.c\
		$(SRC_TEST)vec3d_angle.c\
		$(SRC_TEST)ray_cpy.c\
		$(SRC_TEST)ray_onray.c\
		$(SRC_TEST)ray_equal.c\
		$(SRC_TEST)plane_point.c\
		$(SRC_TEST)plane_ray.c\
		$(SRC_TEST)sphere_ray.c\
		$(SRC_TEST)cylinder.c\
		$(SRC_TEST)conversion.c

MATH =	$(SRC_MATH)vec3d.c\
		$(SRC_MATH)vec3d_util.c\
		$(SRC_MATH)vec3d_util2.c\
		$(SRC_MATH)vec3d_util3.c\
		$(SRC_MATH)ray.c\
		$(SRC_MATH)ray_vec3d.c\
		$(SRC_MATH)ray_util.c\
		$(SRC_MATH)ray_util2.c\
		$(SRC_MATH)change_data.c\
		$(SRC_MATH)plane.c\
		$(SRC_MATH)plane_util.c\
		$(SRC_MATH)sphere.c\
		$(SRC_MATH)RaySphere.c\
		$(SRC_MATH)cylinder.c\
		$(SRC_MATH)cylinder_util.c\

OBJ = ${SRC:.c=.o}

MOBJ = ${MATH:.c=.o}

MA = ${MAIN:.c=.o}

TOBJ = ${TEST:.c=.o}

.PHONY: all clean fclean re libft bonus test norm mlx

all: $(NAME)

$(NAME): libft $(OBJ) $(MOBJ) $(MA) mlx
	@$(CC) $(CFLAGS) $(OBJ) $(MOBJ) $(MA) -o $(NAME) -L libft -lft $(MLXFLAGS)

%.o : %.c
	@$(CC) $(CFLAGS) -c $^ -o $@

test: libft $(OBJ) $(TOBJ) $(MOBJ) mlx
	@$(CC) $(CFLAGS) $(OBJ) $(TOBJ) $(MOBJ) -o $(NAME) -L libft -lft $(MLXFLAGS)
	@ ./$(NAME)
	@ make fclean

norm:
	echo "\033c"
	echo "\nROOT:\n"
	norminette *.c *.h || true
	echo "\nMATH:\n"
	norminette $(SRC_MATH) || true
	echo "\nSRC:\n"
	norminette src/ || true

libft:
	@ make -C libft/

mlx:

	@make -C mlx/

clean:
	@ make clean -C libft/
	@ rm -f $(OBJ) $(MOBJ) $(MA) $(TOBJ)

fclean: clean
	@ make fclean -C libft/
	@ rm -f $(NAME)

re: fclean all 