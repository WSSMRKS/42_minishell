# Directories #
SRCDIR = src/
HDRDIR = headers/
LIBFTDIR = libft/
# Names #
NAME = minishell
# Compiler & Compilation Flags #
COMPILE_OPTIONS =  -g -Werror -Wall -Wextra -lreadline
# Detail on lft means including if libft was called blalibft the command would be -lblalibft it is searching for '.a' and '.so' files
TESTFLAGS = -g3
COMPILE_FLAGS = -g3 -Werror -Wall -Wextra -O0 -c
# ADD SEARCHFLAGS FOR LIBFT ,...
# Compiler #
CC = cc
# Source Files #
SRC = $(SRCDIR)main/minishell.c $(SRCDIR)ui/ui.c $(SRCDIR)executor/ms_executor.c $(SRCDIR)debug/debug.c $(SRCDIR)init/ms_cleanup_utils.c $(SRCDIR)init/ms_init.c $(SRCDIR)ui/tokenizer/lexer.c $(SRCDIR)ui/tokenizer/token_utils.c $(SRCDIR)ui/tokenizer/lexer_quotes.c $(SRCDIR)ui/parser/parser.c $(SRCDIR)ui/parser/make_word.c 
HEADERS = $(HDRDIR)minishell.h $(HDRDIR)ms_parsing.h $(HDRDIR)ms_executor.h $(HDRDIR)ms_garbage.h $(HDRDIR)ms_symtab.h $(HDRDIR)tokenizer.h 

LIBFT_SRC = $(LIBFTDIR)libft.a
# Object Files
SRC_OBJ = $(SRC:.c=.o)
BONUS_OBJ = $(BONUS_SRC:.c=.o)

# Targets #
all: $(NAME)	# Compile the entire project including bonus.

$(NAME): $(LIBFT_SRC) $(SRC_OBJ) # Compile mandatory part.
	$(CC) $(COMPILE_OPTIONS) $(SRC_OBJ) $(LIBFT_SRC) -o $(NAME)

$(LIBFT_SRC): # Download and Compile libft
  ifeq ("$(wildcard $(LIBFTDIR))", "")
	echo "Directory does not exist."
	git clone https://github.com/WSSMRKS/42_libft.git $(LIBFTDIR)
	$(MAKE) all -C $(LIBFTDIR)
  else
	@echo "Skipping download because directory already exists."
	$(MAKE) all -C $(LIBFTDIR)
#	@cp -rf $(LIBFTDIR)libft.h ./
#	@cp -rf $(LIBFTDIR)libft.a ./
  endif

exes: $(NAME) clean # Compile all project parts including bonus clean up after compilation.

# Compile .c to .o #
%.o: %.c
	$(CC) $(COMPILE_FLAGS) $^ -o $@

# Checkers, Testers #

# clean, fclean, re
clean:	# Clean project folders, leave executables.
	rm -f $(SRC_OBJ)
	rm -f $(MAIN_OBJ)
	rm -f $(BONUS_OBJ)
	rm -f $(TEST_OBJ)
  ifeq ("$(wildcard $(LIBFTDIR))", "")
	@echo "libft: Directory does not exist."
  else
	$(MAKE) fclean -C $(LIBFTDIR)
	@echo "libft folder cleaned"
  endif

fclean: clean	# Fully clean project folders.
	rm -f $(NAME) $(BONUS)
	rm -rf $(LIBFTDIR)
	@echo "$(LIBFTDIR) deleted"
	@echo "\"$(NAME)\" deleted"

re: fclean	# Recompile whole project.
	$(MAKE) all

name: # print project name #
	@echo "$(NAME)"

help:	# Print this helpful message
	@awk 'BEGIN { \
	FS = ":.*#"; printf "Usage:\n\tmake <target>\n\nTargets:\n"; } \
	/^[a-zA-Z_0-9-]+:.*?#/ { \
	printf "%-16s%s\n", $$1, $$2 } ' Makefile
# Syntax for this to work: target:	# Description

.PHONY: all fclean clean re name help exes