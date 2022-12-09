
# Unit tests for minishell

CC		= gcc
RM		= rm -f

CFLAGS	= -Wall -Wextra -g3 -fanalyzer

# Libraries
LIBFT	= ../libft/libft.a
LCHECK	= libcheck.a
LINK	= -L../libft -lft -l:libcheck.a -lreadline -lm -lpthread -lrt

# Sources from Minishell
MS_OBJDIR	= ../obj
MS_SRCDIR	= ../src
MS_SOURCE	= ../src/ast.c ../src/stack.c ../src/token_list.c
MS_OBJ		= $(subst ../src/,../obj/,$(MS_SOURCE:.c=.o))

# Sources for unit tests
SOURCE		= data_structures.c
OBJDIR		= obj
OBJ			= $(addprefix $(OBJDIR)/,$(SOURCE:.c=.o))
NAMES		= data_structures_test

all: $(NAMES)

data_structures_test: $(OBJ) $(MS_OBJ) $(LIBFT) $(LCHECK)
	$(CC) $(OBJ) $(MS_OBJ) $(LINK) -o data_structures_test

$(MS_OBJDIR)/%.o:$(MS_SRCDIR)/%.c
	mkdir -p ../obj
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR)/%.o: %.c
	mkdir -p obj
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT):
	make -C ../libft

$(LCHECK):
	./libcheckmk.sh

clean:
	$(RM) $(OBJ) $(MS_OBJ)

fclean: clean
	$(RM) $(NAMES)

.PHONY: clean fclean