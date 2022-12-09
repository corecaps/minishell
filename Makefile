# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: latahbah <latahbah@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/04 12:18:46 by jgarcia           #+#    #+#              #
#    Updated: 2022/12/08 17:49:00 by latahbah         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = gcc
CFLAGS = -Wall -Wextra -Werror
DEBUG = -g3 -fanalywer
LIBFT = libft/libft.a
LINK = -Llibft -lft -lreadline
RM = rm -f
SRCDIR = src
OBJDIR = obj
BIN = bin
SRC = minishell.c		lexer.c
OBJ = $(SRC:.c=.o)
HEADER = *.h
SOURCE = $(addprefix $(SRCDIR)/,$(SRC))
OBJECT = $(addprefix $(OBJDIR)/,$(OBJ))
HEADERS = $(addprefix $(SRCDIR)/,$(HEADER))

all: $(BIN)/$(NAME)

$(BIN)/$(NAME): $(OBJECT) $(LIBFT)
	mkdir -p $(BIN)
	$(CC) $(OBJECT) $(LINK) -o $(BIN)/$(NAME)

debug:	CFLAGS += -g3 -fanalyzer
debug: all

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT):
	make -C libft

clean:
	$(RM) $(OBJECT)
	make clean -C libft

fclean: clean
	$(RM) $(BIN)/$(NAME)
	make fclean -C libft

re: fclean $(BIN)/$(NAME)

norme:
	norminette $(SOURCE)
	norminette $(HEADER)

.PHONY: all re clean fclean norme debug