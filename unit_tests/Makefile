# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jgarcia <jgarcia@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/09 15:54:30 by jgarcia           #+#    #+#              #
#    Updated: 2023/01/09 15:54:32 by jgarcia          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Unit tests for minishell

CC		= gcc
RM		= rm -f

CFLAGS	= -Wall -Wextra -g -fprofile-arcs -ftest-coverage

# Libraries
LIBFT	= ../libft/libft.a
LCHECK	= ./libcheck.a
LINK	= -L../libft -lft libcheck.a -lreadline -lm -lpthread  #-lrt

# Sources from Minishell
MS_OBJDIR	= ../obj
MS_SRCDIR	= ../src
MS_SOURCE	= ../src/token_list.c ../src/ast.c ../src/lexer.c ../src/stack.c ../src/parser.c
MS_SOURCE	+= ../src/grammar_production.c ../src/grammar_production_2.c ../src/exec.c
MS_SOURCE	+= ../src/ast_builder.c ../src/path_expander.c ../src/arguments.c ../src/environ.c
MS_SOURCE	+= ../src/data_utils.c ../src/expand.c ../src/builtin.c ../src/garbage_collector.c
MS_SOURCE	+= ../src/set_env.c ../src/builtin2.c
MS_OBJ		= $(subst ../src/,../obj/,$(MS_SOURCE:.c=.o))
MS_COV		= $(subst ../src/,../obj/,$(MS_SOURCE:.c=.gcno))
MS_COV2		= $(subst ../src/,../obj/,$(MS_SOURCE:.c=.gcda))
# Sources for unit tests
SOURCE		= data_structures.c lexer_test.c parser_test.c exec_test.c main.c environ_test.c
OBJDIR		= obj
OBJ			= $(addprefix $(OBJDIR)/,$(SOURCE:.c=.o))
OBJ_COV		= $(addprefix $(OBJDIR)/,$(SOURCE:.c=.gcno))
OBJ_COV2	= $(addprefix $(OBJDIR)/,$(SOURCE:.c=.gcda))
NAMES		= unit_tests

all: $(NAMES)

unit_tests: $(OBJ) $(MS_OBJ) $(LIBFT) $(LCHECK)
	@echo '====>LINK<===='
	$(CC) $(CFLAGS) $(OBJ) $(MS_OBJ) $(LINK) -o unit_tests
	@./unit_tests > test.log
	@gcov  $(MS_COV) >> test.log
	@mkdir -p gcov
	@mv *.gcov gcov
	@cat test.log
#
#data_structures_test: $(OBJ) $(MS_OBJ) $(LIBFT) $(LCHECK)
#	@$(CC) $(OBJDIR)/data_structures.o $(MS_OBJ) $(LINK) -o data_structures_test
#
#lexer_test:  $(OBJ) $(MS_OBJ) $(LIBFT) $(LCHECK)
#	@$(CC) $(OBJDIR)/lexer_test.o $(MS_OBJ) $(LINK) -o lexer_test
#
#parser_test: $(OBJ) $(MS_OBJ) $(LIBFT) $(LCHECK)
#	@$(CC) $(OBJDIR)/parser_test.o $(MS_OBJ) $(LINK) -o parser_test
#
#exec_test: $(OBJ) $(MS_OBJ) $(LIBFT) $(LCHECK)
#	@$(CC) $(OBJDIR)/exec_test.o $(MS_OBJ) $(LINK) -o exec_test


$(MS_OBJDIR)/%.o:$(MS_SRCDIR)/%.c
	@mkdir -p ../obj
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR)/%.o: %.c
	@mkdir -p obj
	@$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT):
	@make -C ../libft

$(LCHECK):
	./libcheckmk.sh

clean:
	$(RM) $(OBJ) $(MS_OBJ) $(MS_COV) $(MS_COV2) $(OBJ_COV) $(OBJ_COV2) *.gcov

fclean: clean
	$(RM) $(NAMES)

.PHONY: clean fclean
