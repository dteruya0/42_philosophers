# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dteruya <dteruya@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/18 17:05:53 by dteruya           #+#    #+#              #
#    Updated: 2025/04/24 13:38:49 by dteruya          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

SRC_DIR = src
OBJ_DIR = obj

CC = cc
CFLAGS = -Wall -Wextra -Werror

SRCS = main.c parser.c init.c utils.c simulation.c routine.c\

OBJ = $(SRCS:.c=.o)

all: $(OBJ_DIR) $(NAME)

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(NAME): $(addprefix $(OBJ_DIR)/, $(OBJ))
	$(CC) $(CFLAGS) -o $(NAME) $(addprefix $(OBJ_DIR)/, $(OBJ))

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -rf $(OBJ_DIR)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re