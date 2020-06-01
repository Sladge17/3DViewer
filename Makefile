NAME = fdf
FLAG = -Wall -Wextra -Werror

GL_DIR = ./minilibx_macos/
GL_FLAG = -lm -framework OpenGL -framework AppKit
GL = $(GL_DIR)libmlx.a $(GL_FLAG)

LIBFT_DIR = ./libft/
LIBFT = $(LIBFT_DIR)libft.a

HEADER_DIR = ./includes/
HEADER = -I $(HEADER_DIR) -I $(GL_DIR)

SRC_DIR = ./src/
SRC_LIST = fdf.c\
			parser.c\
			parser_support.c\
			parser_fill.c\
			utils.c\
			menu.c\
			menu2.c\
			set_model.c\
			set_scale.c\
			set_system.c\
			def_transform.c\
			transform.c\
			render_mode.c\
			r_vertex.c\
			r_wireframe_noz.c\
			r_wireframe_z.c\
			ortholines.c\
			r_silhouette.c\
			except_quad.c\
			r_mesh1.c\
			r_mesh2.c\
			filltris_zbuf.c\
			except_qmesh.c\
			render_ui.c\
			controls_main.c\
			controls_keybrd.c\
			controls_mouse.c\
			controls_debug.c
SRC = $(addprefix $(SRC_DIR), $(SRC_LIST))

OBJ_DIR = ./obj/
OBJ_LIST = $(patsubst %.c, %.o, $(SRC_LIST))
OBJ = $(addprefix $(OBJ_DIR), $(OBJ_LIST))

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJ)
	@make re -C $(LIBFT_DIR)
	@gcc -o $(NAME) $(HEADER) $(OBJ) $(LIBFT) $(GL)

$(OBJ_DIR)%.o : $(SRC_DIR)%.c $(HEADER_DIR)*.h
	@mkdir -p $(OBJ_DIR)
	@gcc -c $(HEADER) $< -o $@ $(FLAG)

clean:
	@rm -rf $(OBJ_DIR)
	@make clean -C $(LIBFT_DIR)

fclean: clean
	@rm -f $(NAME)
	@make fclean -C $(LIBFT_DIR)

re: fclean all
