# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ksalmi <ksalmi@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/10/14 14:58:42 by ksalmi            #+#    #+#              #
#    Updated: 2020/10/14 15:07:37 by ksalmi           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = lem-in

SRC_NAME = only_debuggin_main.c \
save_info.c \
nodes.c \
links.c \
names.c \
tools.c \

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
	gcc -c $(FLAGS) $(SRCS) $(INCLUDES)
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
