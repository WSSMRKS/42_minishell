# Directories #
SRCDIR = src/
HDRDIR = inc/
LIBFTDIR = libft/
# Names #
NAME = pipex
BONUS = pipex_bonus
# Compiler & Compilation Flags #
COMPILE_OPTIONS =  -g -Werror -Wall -Wextra -L./libft -lft
# Detail on lft means including if libft was called blalibft the command would be -lblalibft it is searching for '.a' and '.so' files
TESTFLAGS = -g3
COMPILE_FLAGS = -g3 -I./inc -I./libft -Werror -Wall -Wextra -O0 -c
# ADD SEARCHFLAGS FOR LIBFT ,...
# Compiler #
CC = cc
# Source Files #
SRC = $(SRCDIR)pipex.c $(SRCDIR)pipex_parsing.c $(SRCDIR)pipex_utils.c $(SRCDIR)pipex_children.c $(SRCDIR)pipex_error.c $(SRCDIR)pipex_here_doc.c
HEADERS = $(HDRDIR)pipex.h
LIBFT_SRC = $(LIBFTDIR)libft.a
# Object Files
SRC_OBJ = $(SRC:.c=.o)
BONUS_OBJ = $(BONUS_SRC:.c=.o)

# Targets #
all: $(NAME)	# Compile the entire project including bonus.
bonus: $(BONUS)	# Compile the bonus part of the project.

$(NAME): $(LIBFT_SRC) $(SRC_OBJ) # Compile mandatory part.
	$(CC) $(COMPILE_OPTIONS) $(SRC_OBJ) $(LIBFT_SRC) -o $(NAME)

$(BONUS): $(LIBFT_SRC) $(SRC_OBJ) # Compile mandatory part.
	$(CC) $(COMPILE_OPTIONS) $(SRC_OBJ) $(LIBFT_SRC) -o $(BONUS)

$(LIBFT_SRC): # Compile libft
	$(MAKE) all -C $(LIBFTDIR)

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
	$(MAKE) fclean -C libft/
	@echo "libft folder cleaned"
  endif

fclean: clean	# Fully clean project folders.
	rm -f $(NAME) $(BONUS)
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
