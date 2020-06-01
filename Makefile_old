NAME = fdf
FLAG = -Wall -Wextra -Werror
GL = -lm -framework OpenGL -framework AppKit

HEADER_DIR = ./includes/
HEADER = -I$(HEADER_DIR) -I ./minilibx_macos/
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
	@$(MAKE) -C ./libft re
	@gcc -o $(NAME) $(HEADER) $(OBJ) ./libft/libft.a ./minilibx_macos/libmlx.a $(GL)

$(OBJ_DIR)%.o : $(SRC_DIR)%.c $(HEADER_DIR)*.h
	@mkdir -p $(OBJ_DIR)
	@gcc -c $(HEADER) $< -o $@ $(FLAG)

clean:
	@rm -rf $(OBJ_DIR)
	@$(MAKE) -C ./libft clean

fclean: clean
	@rm -f $(NAME)
	@$(MAKE) -C ./libft fclean

re: fclean all
