NAME = fdf
FLAG = -Wall -Wextra -Werror
GL = -lmlx -framework OpenGL -framework AppKit

HEADER_DIR = ./includes/
HEADER = -I$(HEADER_DIR)
# HEADER = fdf.h
SRC_DIR = ./src/
SRC_LIST = fdf.c\
			parser.c\
			utils.c\
			set_model.c\
			set_scale.c\
			set_system.c\
			def_transform.c\
			transform.c\
			controls_main.c\
			render_mode.c\
			r_vertex.c\
			r_wireframe_noz.c\
			r_wireframe_z.c\
			ortholines.c\
			parse_color.c\
			r_silhouette.c\
			postfill_quad.c\
			r_mesh1.c\
			r_mesh2.c\
			filltris_zbuf.c\
			postfill_qmesh.c
SRC = $(addprefix $(SRC_DIR), $(SRC_LIST))

OBJ_DIR = ./obj/
OBJ_LIST = $(patsubst %.c, %.o, $(SRC_LIST))
OBJ = $(addprefix $(OBJ_DIR), $(OBJ_LIST))

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJ)
	gcc -o $(NAME) $(HEADER) $(OBJ) ./libft/libft.a $(GL)

$(OBJ_DIR)%.o : $(SRC_DIR)%.c $(HEADER_DIR)*.h
	mkdir -p $(OBJ_DIR)
	# gcc -c $(HEADER) $< -o $@ $(FLAG)
	gcc -c $(HEADER) $< -o $@

clean:
	@rm -rf $(OBJ_DIR)

fclean: clean
	@rm -f $(NAME)

re: fclean all
