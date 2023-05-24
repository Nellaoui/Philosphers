# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nelallao <nelallao@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/22 11:59:39 by nelallao          #+#    #+#              #
#    Updated: 2023/05/22 13:33:47 by nelallao         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
CC = cc
RM = rm -f
# FLAGS = -Wall -Wextra -Werror
SRC = Philosophers.c libft_func.c

all : $(NAME)

$(NAME) :$(SRC)
	@$(CC) $(FLAGS) $(SRC) -o $(NAME)

clean :
	@$(RM) $(OBJ)

fclean : clean
	@$(RM) $(NAME) $(BOUNUS)
re : fclean all
