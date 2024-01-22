# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: glambrig <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/08 16:00:49 by glambrig          #+#    #+#              #
#    Updated: 2024/01/22 15:51:42 by glambrig         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: all clean fclean re

NAME = philo

CC = gcc

CFLAGS = -Wall -Wextra -lpthread -g #-Werror

SRC = philo.c \
		utils.c \
		2utils.c \
		error_checks.c \
		time.c \
		2algo.c \
		algo.c \
			
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