# Names #
NAME = libft.a
MAIN_NAME = a.out
# Compiler & COptions & CFlags #
CFLAGS = -g -Werror -Wall -Wextra
COPTIONS = -c
CC = cc
# Source Files #
SRC =  	ft_atoi.c		ft_itoa.c		ft_putnbr_fd.c	ft_strlcpy.c	ft_tolower.c	\
		ft_bzero.c		ft_memchr.c		ft_putstr_fd.c  ft_strlen.c		ft_toupper.c	\
		ft_calloc.c		ft_memcmp.c 	ft_split.c		ft_strmapi.c	ft_isalnum.c	\
		ft_memcpy.c		ft_strchr.c		ft_strncmp.c	ft_isalpha.c	ft_memmove.c	\
		ft_strdup.c		ft_strnstr.c	ft_isascii.c	ft_memset.c		ft_striteri.c	\
		ft_strrchr.c	ft_isdigit.c	ft_putchar_fd.c	ft_strjoin.c	ft_strtrim.c	\
		ft_isprint.c	ft_putendl_fd.c	ft_strlcat.c	ft_substr.c
ADDON = ft_printf.c		ft_printf_err.c	ft_pnb_b_fd.c	ft_pnb_b_fd_s.c	helper_functions.c	\
		ft_putstr_non_printable.c	ft_countwords.c 	ft_atol.c 	get_next_line.c	ft_abs.c \
		ft_free_2d.c	ft_free_3d.c	ft_fprintf.c
BONUS_SRC = 	ft_lstadd_back.c	ft_lstadd_front.c		ft_lstclear.c	\
				ft_lstdelone.c	ft_lstister.c			ft_lstlast.c	\
				ft_lstmap.c		ft_lstnew.c			ft_lstsize.c
MAIN_SRC = main.c
TEST_SRC = ft_putstr_non_printable.c

HEADERS = libft.h

# Object Files #
SRC_OBJ = $(SRC:.c=.o)
ADDON_OBJ = $(ADDON:.c=.o)
BONUS_OBJ = $(BONUS_SRC:.c=.o)
MAIN_OBJ = $(MAIN_SRC:.c=.o)
TEST_OBJ = $(TEST_SRC:.c=.o)

# Targets #
all : $(NAME)
bonus : all

$(NAME): $(BONUS_OBJ) $(SRC_OBJ) $(ADDON_OBJ)
	ar rcs $(NAME) $(SRC_OBJ) $(BONUS_OBJ) $(ADDON_OBJ)

base: $(SRC_OBJ)
	ar rcs $(NAME) $(SRC_OBJ)

# test: $(MAIN_OBJ) $(NAME) $(TEST_OBJ) $(BONUS_OBJ)
# 	@$(CC) $(CFLAGS) $(MAIN_OBJ) $(SRC_OBJ) $(TEST_OBJ) $(BONUS_OBJ) -o $(MAIN_NAME)
# 	@echo "test command sucessfully executed. Executable is called \"$(MAIN_NAME)\"!"

# run: fclean test bonus
# 	@echo "\"a.out\" execution below!"
# 	@./a.out | cat -e

# debug: fclean test bonus
# 	gdb ./a.out

# Compile .c to .o #
%.o: %.c
	@$(CC) $(CFLAGS) $(COPTIONS) $^ -o $@

clean:
	@rm -f $(SRC_OBJ) $(MAIN_OBJ) $(BONUS_OBJ) $(TEST_OBJ) $(ADDON_OBJ)
	@echo "Working folder clean."

fclean: clean
	@rm -f $(NAME) $(MAIN_NAME)
	@echo "\"$(NAME)\" deleted"

re: fclean all

name:
	@echo "$(NAME)"

help:
	@echo "Possible Commands:"
	@echo "all --> Compile whole project"
	@echo "name --> Display project name"
	@echo "base --> Compile only core functions without bonus"
#	@echo "test --> Compile main if available"
#	@echo "run --> Run main if available"
#	@echo "debug --> Run GDB with a.out"
	@echo "clean --> Delete all object files, leave executable"
	@echo "fclean --> Delete everything besides source files"
	@echo "re --> recompile everything (fclean, all)"

.PHONY: all name test run bonus debug fclean clean re help base
