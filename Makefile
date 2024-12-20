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
	ui/token/token_scan.c \
	ui/token/token_util.c \
	ui/token/tokenize.c \
	ui/token/util.c \
	ui/token/unescape.c \
	ui/token/normalize.c \
	ui/token/normalize2.c \
	ui/token/span_printerr.c \
	ui/parse/ast_printerr.c \
	ui/parse/parse.c \
	ui/parse/parse_redir.c \
	ui/parse/parser.c \
	ui/parse/parser_impl.c \
	ui/parse/util.c \
	ui/parse/util2.c \
	ui/parse/util3.c \
	ui/ast/ast.c \
	ui/ast/free_ast.c \
	ui/prompt.c \
	ui/ui.c \
	ui/ui_util.c \
	main/minishell.c \
	init/ms_cleanup_utils.c \
	init/ms_cleanup_utils2.c \
	init/ms_cleanup_utils3.c \
	init/ms_init.c \
	executor/ms_env.c \
	executor/ms_env2.c \
	executor/ms_env3.c \
	executor/ms_env4.c \
	executor/ms_error.c \
	executor/ms_executor.c \
	executor/ms_executor2.c \
	executor/ms_executor3.c \
	executor/ms_executor4.c \
	executor/ms_ex_redir.c \
	executor/ms_heredoc.c \
	executor/ms_heredoc2.c \
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

$(NAME): $(LIBFT_SRC) $(SRC_OBJ) # Compile mandatory part. # maybe need? -L$(LIBFTDIR) -lft
	$(CC) $(SRC_OBJ) $(LIBFT_SRC) $(COMPILE_OPTIONS) -o $(NAME)

$(LIBFT_SRC): # Compile libft
	$(MAKE) all -C $(LIBFTDIR) CFLAGS='$(COMPILE_FLAGS)'

# clean, fclean, re
clean:	# Clean project folders, leave executables.
	rm -f $(SRC_OBJ)
	$(MAKE) fclean -C $(LIBFTDIR)
	@echo "libft folder cleaned"

fclean: clean	# Fully clean project folders.
	rm -f $(NAME)
	@echo "\"$(NAME)\" deleted"

re: fclean	# Recompile whole project.
	$(MAKE) all

.PHONY: all fclean clean re
.NOTPARALLEL: $(LIBFT_SRC)
