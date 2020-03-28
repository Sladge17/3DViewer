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
			set_background.c\
			set_scale.c\
			transform.c\
			controls_main.c\
			drawing.c\
			r_vertex.c\
			r_wireframe_noz.c\
			r_wireframe_z.c
			# controls.c\
			# transform.c\
			# drawing.c\
			# draw_line.c\
			# fill_triangle.c\
			# def_data.c\
			# parser.c
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
