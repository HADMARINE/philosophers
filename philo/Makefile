# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lhojoon <lhojoon@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/18 14:31:50 by lhojoon           #+#    #+#              #
#    Updated: 2024/05/20 18:33:10 by lhojoon          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
CC = cc
CFLAGS = -Wall -Wextra -Werror
DEBUG = -g

DIR = srcs
SRCS_RAW =	main.c \
			ft_atoi.c \
			init_values.c \
			execute.c \
			utils.c \
			execute_2.c \
			init_values_2.c \
			execute_3.c \
			free_philo.c \
			verify_input.c
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