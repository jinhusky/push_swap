# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kationg <kationg@student.42kl.edu.my>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/06/10 09:39:18 by kationg           #+#    #+#              #
#    Updated: 2025/07/24 13:59:54 by kationg          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = push_swap

SRCS = srcs/main.c srcs/operations.c srcs/parsing.c srcs/ranking.c srcs/small_sorts.c srcs/utils.c srcs/free_mem.c

OBJ_SRCS = $(SRCS:.c=.o)

FLAGS = -Wall -Wextra -Werror

INCLUDES = -Ilibft -Iincludes

CC = cc

$(NAME): $(OBJ_SRCS)
	make -C libft all
	$(CC) $(FLAGS) $(INCLUDES) $(OBJ_SRCS) libft/libft.a -o $@

%.o : %.c
	$(CC) $(FLAGS) $(INCLUDES) -c $< -o $@

all: $(NAME)

clean:
	make -C libft clean
	rm -f $(OBJ_SRCS)

fclean: clean
	make -C libft fclean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
