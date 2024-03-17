# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lhojoon <lhojoon@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/18 14:31:50 by lhojoon           #+#    #+#              #
#    Updated: 2024/03/17 22:21:00 by lhojoon          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
CC = gcc
CFLAGS = -Wall -Wextra -Werror

DIR = srcs
SRCS_RAW =	main.c \
			ft_atoi.c \
			init_values.c \
			execute.c \
			utils.c \
			execute_2.c \
			init_values_2.c \
			execute_3.c
SRCS = $(addprefix $(DIR)/,$(SRCS_RAW))
OBJS = $(SRCS:c=o)
INCLUDES = -I./includes

all: $(NAME)
$(NAME): $(OBJS)
	$(CC) $(OBJS) $(DEBUG) -o $(NAME)
clean:
	rm $(OBJS) $(OBJB) -f
fclean: clean
	rm $(NAME) -f
re: fclean all
%.o: %.c
	$(CC) -c $< -o $@ $(CFLAGS) $(INCLUDES) $(DEBUG)