NAME = test_libft
CFLAGS = -Wall -Wextra -Werror -O3 -flto
# CFLAGS = -Wall -Wextra -Werror -g -Og

LIBFTDIR = ../

SRCS = \
	test.c\
	arr_qsort.c\

OBJ = $(SRCS:.c=.o)

%.o: %.c
	cc $(CFLAGS) -c -I$(LIBFTDIR) $< -o $@

all: $(NAME)

$(NAME): $(OBJ)
	$(MAKE) -C $(LIBFTDIR) CFLAGS='$(CFLAGS)'
	cc $(CFLAGS) $(OBJ) -L$(LIBFTDIR) -lft -o $(NAME)

debug: CFLAGS += -DDEBUG
debug: all

clean:
	$(MAKE) -C $(LIBFTDIR) clean
	rm -f $(OBJ)

fclean: clean
	$(MAKE) -C $(LIBFTDIR) fclean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
