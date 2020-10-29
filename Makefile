# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: orantane <orantane@student.hive.fi>	    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/10/14 14:58:42 by ksalmi            #+#    #+#              #
#    Updated: 2020/10/27 17:12:34 by ksalmi           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = lem-in

SRC_NAME = only_debuggin_main.c \
save_info.c \
nodes.c \
links.c \
names.c \
tools.c \
tools2.c \
path.c \
print.c \
path_select.c \
error.c \
build_link_tree.c \
avoid.c \

SRC_DIR = src/

LIB_DIR = lib/

LIB = lib/libft.a

OBJ_DIR = obj/

INCLUDES = -I includes/ -I lib/includes/

SRCS = $(addprefix $(SRC_DIR),$(SRC_NAME))

OBJ = $(subst .c,.o,$(SRC_NAME))

OBJECTS = $(addprefix $(OBJ_DIR),$(OBJ))

FLAGS = -Wall -Wextra -Werror

.PHONY: all clean fclean re

all: $(NAME)

$(NAME):
	make -C $(LIB_DIR)
	gcc -g -c $(FLAGS) $(SRCS) $(INCLUDES)
	mkdir -p $(OBJ_DIR)
	mv -f $(OBJ) $(OBJ_DIR)
	gcc $(FLAGS) $(OBJECTS) $(INCLUDES) $(LIB) -o $(NAME)
	@echo $(NAME) "compiled..."

clean:
	make clean -C $(LIB_DIR)
	/bin/rm -f $(OBJECTS)
	/bin/rm -rf $(OBJ_DIR)

fclean: clean
	make fclean -C $(LIB_DIR)
	/bin/rm -f $(NAME)

re: fclean all
