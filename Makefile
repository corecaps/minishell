# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jgarcia <jgarcia@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/04 12:18:46 by jgarcia           #+#    #+#              #
#    Updated: 2022/12/05 11:37:17 by jgarcia          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = gcc
CFLAGS = -Wall -Wextra -Werror
DEBUG = -g3 -fanalyzer
LIBFT = libft/libft.a
LINK = -Llibft -lft -lreadline
RM = rm -f
SRCDIR = src
OBJDIR = obj
BIN = bin
SRC = minishell.c token_list.c ast.c
OBJ = $(SRC:.c=.o)
HEADER = minishell.h data_structures.h
SOURCE = $(addprefix $(SRCDIR)/,$(SRC))
OBJECT = $(addprefix $(OBJDIR)/,$(OBJ))
HEADERS = $(addprefix $(SRCDIR)/,$(HEADER))
UNITTESTS = unit_tests/data_structures_test

all: norme test $(BIN)/$(NAME)

$(BIN)/$(NAME): $(OBJECT) $(LIBFT)
	@echo '====>LINK<===='
	@mkdir -p $(BIN)
	$(CC) $(OBJECT) $(LINK) -o $(BIN)/$(NAME)

debug:	CFLAGS += -g3 -fanalyzer
debug: all

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@echo '====>COMPILATION<===='
	@mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT):
	@make -C libft

test: $(UNITTESTS)
	@echo '====>UNIT TESTS<===='
	./unit_tests/data_structures_test

$(UNITTESTS):
	@make -C unit_tests

clean:
	$(RM) $(OBJECT)
	make clean -C libft
	make fclean -C unit_tests

fclean: clean
	$(RM) $(BIN)/$(NAME)
	make fclean -C libft

re: fclean $(BIN)/$(NAME)

norme:
	@echo '====>NORME<===='
	norminette $(SOURCE)
	norminette $(HEADERS)

.PHONY: all re clean fclean norme debug test