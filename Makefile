NAME =		miniRT
SOURSE =	main.c \
			error_exit.c \
			global_init.c \
			parsing/parsing_read_file.c \
			parsing/parsing_scene_description.c \
			parsing/parsing_scene_description_2.c \
			parsing/parsing_elements.c \
			parsing/get_objects.c \
			parsing/parsing_specular_reflection.c \
			bonus_triangles/parsing_ts_file.c \
			bonus_triangles/parsing_element_ts.c \
			color.c \
			vector_producte.c \
			vector.c \
			textures.c \
			apply_textures.c \
			free_global.c bmp_texture.c key_hook.c\
			rotate1.c render.c intersept_sphere.c intersept_cylin.c   checboard.c    light.c   intersept_scene.c    

OBJ = $(SOURSE:%.c=%.o)

LIBFT_LIB	=	libft.a
LIBFT_DIR	=	./libft/
MLX_DIR		=	./mlx
LIBFT		=	${LIBFT_DIR}${LIBFT_LIB}

all:$(NAME)
%.o: %.c rt.h
	cc  -Wall -Wextra -Werror -g -O3 -Imlx  -c -o $@ $<

$(NAME): $(OBJ) $(SOURSE) Makefile
	@make -C $(MLX_DIR) all
	@make -C $(LIBFT_DIR) all
	cc $(OBJ) $(LIBFT) -Wall -Wextra -Werror -g -O3  -Lmlx -lmlx -framework OpenGL -framework AppKit -o $(NAME)

clean:
	@make -C $(MLX_DIR) clean
	@make -C $(LIBFT_DIR) clean
	@/bin/rm -f $(OBJ)
	@echo "clean"

fclean: clean
	@make -C $(MLX_DIR) clean
	@make -C $(LIBFT_DIR) fclean
	@/bin/rm -f $(NAME) 
	@echo "fclean"

re: fclean all

.PHONY:	all re clean fclean