# Directories #
SRCDIR = src/
HDRDIR = headers/
LIBFTDIR = libft/
# Names #
NAME = minishell
# Compiler & Compilation Flags #
COMPILE_OPTIONS = $(COMPILE_FLAGS) -lreadline
COMPILE_FLAGS = -Werror -Wall -Wextra -g3
# Compiler #
CC = cc
# Source Files #
SRC_FILES = \
	ui/token/expand.c \
	ui/token/token.c \
	ui/token/tokenize.c \
	ui/token/util.c \
	ui/token/unescape.c \
	ui/token/normalize.c \
	ui/parse/parse.c \
	ui/parse/parser.c \
	ui/ast.c \
	ui/ui.c \
	main/minishell.c \
	init/ms_cleanup_utils.c \
	init/ms_init.c \
	executor/ms_env.c \
	executor/ms_env2.c \
	executor/ms_env3.c \
	executor/ms_env4.c \
	executor/ms_error.c \
	executor/ms_executor.c \
	executor/ms_ex_redir.c \
	executor/ms_heredoc.c \
	builtins/ms_cd.c \
	builtins/ms_echo.c \
	builtins/ms_env.c \
	builtins/ms_exit.c \
	builtins/ms_export.c \
	builtins/ms_pwd.c \
	builtins/ms_unset.c

# debug/debug.c
HEADER_FILES = minishell.h \
	ms_parsing.h \
	ms_executor.h \
	ms_garbage.h \
	ms_stab.h \
	tokenizer.h
SRC = $(addprefix $(SRCDIR), $(SRC_FILES))
HEADERS = $(addprefix $(HDRDIR), $(HEADER_FILES))

LIBFT_SRC = $(LIBFTDIR)libft.a
# Object Files
SRC_OBJ = $(SRC:.c=.o)

# Compile .c to .o #
%.o: %.c
	$(CC) -c $(COMPILE_FLAGS) $^ -o $@

# Targets #
all: $(NAME)	# Compile the entire project including bonus.

nodbg: COMPILE_FLAGS = -Werror -Wall -Wextra -g3 -DNO_DEBUG=1
nodbg: $(NAME)

$(NAME): $(LIBFT_SRC) $(SRC_OBJ) # Compile mandatory part. # maybe need? -L$(LIBFTDIR) -lft
	$(CC) $(SRC_OBJ) $(LIBFT_SRC) $(COMPILE_OPTIONS) -o $(NAME)

$(LIBFT_SRC): # Download and Compile libft
  ifeq ("$(wildcard $(LIBFTDIR))", "")
	echo "Directory does not exist."
	git clone https://github.com/WSSMRKS/ms_libft.git $(LIBFTDIR)
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

re: fclean	# Recompile whole project.
	$(MAKE) all

name: # print project name #
	@echo "$(NAME)"

supps: all
	./create_rl_suppressions.sh

exv: all
	valgrind --suppressions=suppressions.supp --track-fds=yes --leak-check=full --show-leak-kinds=all ./minishell

exvs: all
	valgrind --suppressions=suppressions.supp --gen-suppressions=all --leak-check=full --show-leak-kinds=all ./minishell

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

.PHONY: all fclean clean re name help exes exv exvs exval ex pargs supps
.NOTPARALLEL: $(LIBFT_SRC)
