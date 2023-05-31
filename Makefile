# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nelallao <nelallao@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/22 11:59:39 by nelallao          #+#    #+#              #
#    Updated: 2023/05/31 18:44:47 by nelallao         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
CC = cc
RM = rm -f
FLAGS = -Wall -Wextra -Werror
SRC = Philosophers.c checks.c outils.c routine.c

all : $(NAME)

# FLAGS = -fsanitize=thread -g

$(NAME) :$(SRC)
	@$(CC) $(FLAGS) $(SRC) -o $(NAME)


clean :
	@$(RM) $(OBJ)

fclean : clean
	@$(RM) $(NAME)
re : fclean all
