# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jcesar-s <jcesar-s@student.42porto.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/09/17 17:35:17 by jcesar-s          #+#    #+#              #
#    Updated: 2025/09/28 15:08:06 by jcesar-s         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
CC = cc
CFLAGS = -Wall -Wextra -Werror -g -pthread
IDIR = include/
ODIR = obj/
SDIR = src/
SRCFILES = main.c \
		   utils.c \
		   create_table.c \
		   start_meal.c \
		   philo_eat.c \
		   philo_sleep.c
SRC = $(patsubst %, $(SDIR)%, $(SRCFILES))
OBJ = $(patsubst %.c, $(ODIR)%.o, $(SRCFILES))
DEP = $(IDIR)philo.h

all: $(NAME)

$(NAME): $(OBJ) 
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

$(ODIR)%.o: $(SDIR)%.c $(DEP)
	mkdir -p $(ODIR)
	$(CC) $(CFLAGS) -c $< -o $@ -I $(IDIR)

clean:
	rm -rf $(ODIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re bonus
