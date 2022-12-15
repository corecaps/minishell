# Unit tests for minishell

CC		= gcc
RM		= rm -f

CFLAGS	= -Wall -Wextra -g

# Libraries
LIBFT	= ../libft/libft.a
LCHECK	= ./libcheck.a
LINK	= -L../libft -lft libcheck.a -lreadline -lm -lpthread #-lrt

# Sources from Minishell
MS_OBJDIR	= ../obj
MS_SRCDIR	= ../src
MS_SOURCE	= ../src/token_list.c ../src/ast.c ../src/lexer.c ../src/free_cmd.c ../src/stack.c ../src/parser.c
MS_SOURCE	+= ../src/grammar_production.c ../src/grammar_production_2.c
MS_OBJ		= $(subst ../src/,../obj/,$(MS_SOURCE:.c=.o))

# Sources for unit tests
SOURCE		= data_structures.c lexer_test.c
OBJDIR		= obj
OBJ			= $(addprefix $(OBJDIR)/,$(SOURCE:.c=.o))
NAMES		= data_structures_test lexer_test

all: $(NAMES)

data_structures_test: $(OBJ) $(MS_OBJ) $(LIBFT) $(LCHECK)
	@$(CC) $(OBJDIR)/data_structures.o $(MS_OBJ) $(LINK) -o data_structures_test

lexer_test:  $(OBJ) $(MS_OBJ) $(LIBFT) $(LCHECK)
	@$(CC) $(OBJDIR)/lexer_test.o $(MS_OBJ) $(LINK) -o lexer_test

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
	$(RM) $(OBJ) $(MS_OBJ)

fclean: clean
	$(RM) $(NAMES)

.PHONY: clean fclean