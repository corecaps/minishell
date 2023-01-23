# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: latahbah <latahbah@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/04 12:18:46 by jgarcia           #+#    #+#              #
#    Updated: 2023/01/17 10:26:12 by latahbah         ###   ########.fr        #
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
SRC =	minishell.c				token_list.c			ast.c \
		lexer.c					stack.c					parser.c \
		grammar_production.c	grammar_production_2.c	ast_builder.c \
		exec.c					path_expander.c			arguments.c \
		environ.c				data_utils.c			expand.c \
		builtin.c				builtin2.c				garbage_collector.c \
		set_env.c				signal_handler.c		lexer2.c \
		find_binary.c			ast_node_init.c			heredoc_parse.c \
		check_builtin.c			cmd_line.c 				print_sorted_env.c\
		single_cmd.c			exec_heredoc.c			exec_leaf.c \
		runners.c				exec_utils.c			traverse_pipe.c \
		prompt.c				export.c				error.c

OBJ = $(SRC:.c=.o)
HEADER = minishell.h data_structures.h
SOURCE = $(addprefix $(SRCDIR)/,$(SRC))
OBJECT = $(addprefix $(OBJDIR)/,$(OBJ))
HEADERS = $(addprefix $(SRCDIR)/,$(HEADER))
UNITTESTS = unit_tests/unit_tests

all: $(BIN)/$(NAME)

$(BIN)/$(NAME): $(OBJECT) $(LIBFT)
	@echo '====>LINK<===='
	@mkdir -p $(BIN)
	$(CC) $(OBJECT) $(LINK) -o $(BIN)/$(NAME)

debug:	CFLAGS += -g
debug: all

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@echo '====>COMPILATION<===='
	@mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT):
	@echo '====>BUILDING LIBFT<===='
	@make -C libft

test: $(UNITTESTS)
	@echo '====>RUNNING UNIT TESTS<===='
	@./unit_tests/unit_tests

$(UNITTESTS):
	@echo '====>BUILDING UNIT TESTS<===='
	@make -C unit_tests

exit_code: utils/exit_code.c
	gcc utils/exit_code.c -o bin/exit_code

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