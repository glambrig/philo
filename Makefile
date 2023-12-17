# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: glambrig <glambrig@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/08 16:00:49 by glambrig          #+#    #+#              #
#    Updated: 2023/12/17 17:09:11 by glambrig         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: all clean fclean re

NAME = philo

CC = gcc

CFLAGS = -Wall -Wextra -Werror -lpthread -g

SRC = utils.c \
	error_checks.c \
	philo.c \
	init.c \
	actual_algo.c
	
OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(SRC) -o $@ $(CFLAGS)

$(OBJ): %.o : %.c
	$(CC) -c $< -o $@ $(CFLAGS)

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all