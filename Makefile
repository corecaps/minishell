# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: latahbah <latahbah@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/04 12:18:46 by jgarcia           #+#    #+#              #
#    Updated: 2022/12/20 10:47:03 by latahbah         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = gcc
CFLAGS = -Wall -Wextra
DEBUG = -g3 -fanalyzer
LIBFT = libft/libft.a
LINK = -Llibft -lft -lreadline
RM = rm -f
SRCDIR = src
OBJDIR = obj
BIN = bin
SRC =	minishell.c \
		token_list.c \
		ast.c \
		lexer.c \
		stack.c \
		parser.c \
		grammar_production.c \
		grammar_production_2.c\
		ast_builder.c \
		exec.c \
		path_expander.c \
		arguments.c

OBJ = $(SRC:.c=.o)
HEADER = minishell.h data_structures.h
SOURCE = $(addprefix $(SRCDIR)/,$(SRC))
OBJECT = $(addprefix $(OBJDIR)/,$(OBJ))
HEADERS = $(addprefix $(SRCDIR)/,$(HEADER))
UNITTESTS = unit_tests/data_structures_test unit_tests/lexer_test unit_tests/parser_test unit_tests/exec_test

all: test $(BIN)/$(NAME)

$(BIN)/$(NAME): $(OBJECT) $(LIBFT)
	@echo '====>LINK<===='
	@mkdir -p $(BIN)
	$(CC) $(OBJECT) $(LINK) -o $(BIN)/$(NAME)

debug:	CFLAGS += -g3 
debug: all

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@echo '====>COMPILATION<===='
	@mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@ | pv -L 10k -N "Compiling $@"

$(LIBFT):
	@echo '====>BUILDING LIBFT<===='
	@make -C libft

test: $(UNITTESTS)
	@echo '====>RUNNING UNIT TESTS<===='
	@echo '====>Testing : Data Structures<===='
	./unit_tests/data_structures_test
	@echo '====>Testing : Lexer<===='
	./unit_tests/lexer_test
	@echo '====>Testing : Parser<===='
	./unit_tests/parser_test
	@echo '====>Testing : Exec<===='
	./unit_tests/exec_test

$(UNITTESTS):
	@echo '====>BUILDING UNIT TESTS<===='
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