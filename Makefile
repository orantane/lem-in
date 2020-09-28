# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: orantane <orantane@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/17 16:20:24 by orantane          #+#    #+#              #
#    Updated: 2020/08/21 20:44:56 by orantane         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = orantane.filler

SRC = srcs/*.c

OBJ = *.o

LIB = libft/libft.a

HEADER = includes/filler.h

FLAGS = -Wall -Wextra -Werror

RUN_LIB = make --no-print-directory -C libft/

all: 
	@$(RUN_LIB)
	@make --no-print-director $(NAME)

$(NAME): $(OBJ)
	gcc $(FLAGS) -o $(NAME) $(OBJ) $(LIB) -I $(HEADER)

$(OBJ):
	gcc $(FLAGS) -c $(SRC) -I $(HEADER)

re: fclean all

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

.PHONY = all re clean fclean
