NAME = miniRT

SOURCES = main.c ops_on_point.c ops_on_vector.c mag_norm_dot_cros.c colors.c batch.c \
          matrix_4_4.c matrix_inverse.c transforms.c tuple_rotation.c extra.c ops_on_ray.c \
		  form_shapes.c light_shade.c for_render.c inspect_intersect.c cylinder.c \
		  parsing.c get_next_line.c get_next_line_utils.c errors.c\

OBJECTS = $(SOURCES:%.c=%.o)

LIBX = ./resources/mlx/libmlx.a
LIBFTBF = ./resources/ft_libft_printf/libftprintf.a

CC = cc
CFLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME):$(OBJECTS)
	$(MAKE) -C ./resources/mlx
	$(MAKE)	-C ./resources/ft_libft_printf
	$(CC) -o $(NAME) $(SOURCES) $(LIBX) $(LIBFTBF)  -framework OpenGL -framework AppKit

clean:
	$(MAKE) clean -C ./resources/mlx
	$(MAKE) clean -C ./resources/ft_libft_printf
	/bin/rm -f $(OBJECTS)

fclean: clean
	$(MAKE) fclean -C ./resources/ft_libft_printf
	/bin/rm -f $(NAME) $(BNAME)

re: fclean all

test: all
	./$(NAME) test.rt