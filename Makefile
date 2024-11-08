# Directories #
SRCDIR = src/
HDRDIR = headers/
LIBFTDIR = libft/
# Names #
NAME = minishell
# Compiler & Compilation Flags #
COMPILE_OPTIONS = $(COMPILE_FLAGS) -lreadline
COMPILE_FLAGS = -g3 -Werror -Wall -Wextra -Og
# Compiler #
CC = cc
# Source Files #
SRC_FILES = main.c \
	ui/token/token.c \
	ui/token/tokenize.c \
	ui/token/util.c
	# main/minishell.c \
	# ui/ui.c \
	# debug/debug.c \
	# init/ms_cleanup_utils.c \
	# init/ms_init.c \
	# executor/ms_env.c \
	# ui/tokenizer/lexer.c \
	# ui/tokenizer/token_utils.c \
	# ui/tokenizer/lexer_quotes.c \
	# ui/parser/parser.c \
	# ui/parser/make_word.c \
	# executor/ms_builtins.c
HEADER_FILES = minishell.h \
	ms_parsing.h \
	ms_executor.h \
	ms_garbage.h \
	ms_symtab.h \
	tokenizer.h
SRC = $(addprefix $(SRCDIR), $(SRC_FILES))
HEADERS = $(addprefix $(HDRDIR), $(HEADER_FILES))

LIBFT_SRC = $(LIBFTDIR)libft.a
# Object Files
SRC_OBJ = $(SRC:.c=.o)

# Compile .c to .o #
%.o: %.c # maybe need? -I$(LIBFTDIR)
	$(CC) -c $(COMPILE_FLAGS) $^ -o $@

# Targets #
all: $(NAME)	# Compile the entire project including bonus.

$(NAME): $(SRC_OBJ) $(LIBFT_SRC) # Compile mandatory part. # maybe need? -L$(LIBFTDIR) -lft
	$(CC) $(SRC_OBJ) $(LIBFT_SRC) $(COMPILE_OPTIONS) -o $(NAME)

$(LIBFT_SRC): # Download and Compile libft
  ifeq ("$(wildcard $(LIBFTDIR))", "")
	echo "Directory does not exist."
	git clone https://github.com/kjzl/42_libft.git $(LIBFTDIR)
	$(MAKE) all -C $(LIBFTDIR) CFLAGS='$(COMPILE_FLAGS)'
  else
	@echo "Skipping download because directory already exists."
	$(MAKE) all -C $(LIBFTDIR) CFLAGS='$(COMPILE_FLAGS)'
  endif

exes: $(NAME) clean # Compile all project parts including bonus clean up after compilation.

# clean, fclean, re
clean:	# Clean project folders, leave executables.
	rm -f $(SRC_OBJ)
  ifeq ("$(wildcard $(LIBFTDIR))", "")
	@echo "libft: Directory does not exist."
  else
	$(MAKE) fclean -C $(LIBFTDIR)
	@echo "libft folder cleaned"
  endif

fclean: clean	# Fully clean project folders.
	rm -f $(NAME)
	rm -rf $(LIBFTDIR)
	@echo "$(LIBFTDIR) deleted"
	@echo "\"$(NAME)\" deleted"

re: fclean	all# Recompile whole project.

name: # print project name #
	@echo "$(NAME)"

exv: all
	valgrind --suppressions=suppressions2.supp --leak-check=full --show-leak-kinds=all ./minishell

exvs: all
	valgrind --suppressions=suppressions2.supp --gen-suppressions=all --leak-check=full --show-leak-kinds=all ./minishell

exval: all
	valgrind --leak-check=full --show-leak-kinds=all ./minishell

ex: all
	./minishell

help:	# Print this helpful message
	@awk 'BEGIN { \
	FS = ":.*#"; printf "Usage:\n\tmake <target>\n\nTargets:\n"; } \
	/^[a-zA-Z_0-9-]+:.*?#/ { \
	printf "%-16s%s\n", $$1, $$2 } ' Makefile
# Syntax for this to work: target:	# Description

pargs:
	gcc src/debug/print_args.c -o pargs

.PHONY: all fclean clean re name help exes exv exvs exval ex pargs
.NOTPARALLEL: $(LIBFT_SRC)
