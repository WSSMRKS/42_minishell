# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: zblume <zblume@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/14 10:19:33 by zblume            #+#    #+#              #
#    Updated: 2024/06/29 14:36:15 by zblume           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

BLACK   = \033[0;30m
RED     = \033[0;31m
GREEN   = \033[0;32m
YELLOW  = \033[0;33m
BLUE    = \033[0;34m
MAGENTA = \033[0;35m
CYAN    = \033[0;36m
WHITE   = \033[0;37m
RESET   = \033[0m

CC = cc
CFLAGS = -Wall -Wextra -Werror

GNL_DIR = get_next_line
GNL_SRC = $(addprefix $(GNL_DIR)/, \
		get_next_line_bonus.c get_next_line_utils_bonus.c)

PRINTF_DIR = printf
PRINTF_SRC = $(addprefix $(PRINTF_DIR)/, \
		ft_printf.c ft_putfunct.c ft_hexconvert.c)

FUNC_DIRS = $(GNL_DIR) $(PRINTF_DIR)
FUNC_SRCS = $(GNL_SRC) $(PRINTF_SRC)

SRC_DIR = ./src
SRC = $(addprefix $(SRC_DIR)/, \
		ft_atoi.c ft_bzero.c ft_calloc.c ft_isalnum.c ft_isalpha.c ft_isascii.c \
		ft_isdigit.c ft_isprint.c ft_itoa.c ft_memchr.c ft_memcmp.c ft_memcpy.c \
		ft_memmove.c ft_memset.c ft_putchar_fd.c ft_putendl_fd.c ft_putstr_fd.c \
		ft_putnbr_fd.c ft_split.c ft_strchr.c ft_strdup.c ft_strjoin.c ft_strlcat.c \
		ft_strlcpy.c ft_strlen.c ft_strmapi.c ft_strncmp.c ft_strnstr.c ft_strrchr.c \
		ft_striteri.c ft_strtrim.c ft_substr.c ft_tolower.c ft_toupper.c \
		ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c ft_lstadd_back.c \
		ft_lstdelone.c ft_lstclear.c ft_lstiter.c ft_lstmap.c \
		$(FUNC_SRCS))

OBJ_DIR = ./obj
OBJ = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRC))

NAME = libft.a
OPTIONS = -c

all: $(NAME)

$(NAME): $(OBJ)
	@ar rc $(NAME) $(OBJ)
	@printf "$(GREEN)$(NAME) created$(RESET)\n"
	@printf "$(MAGENTA)"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	@mkdir -p $(OBJ_DIR)/$(GNL_DIR)
	@mkdir -p $(OBJ_DIR)/$(PRINTF_DIR)
	@$(CC) $(CFLAGS) $(OPTIONS) $< -o $@
	@printf "$(BLUE)Compiling...$(CYAN) $<$(RESET)\n"

clean:
	@rm -rf $(OBJ_DIR)
	@printf "$(RED)Libft Objects removed$(RESET)\n"
	@printf "$(MAGENTA)"
	
fclean: clean
	@rm -f $(NAME)
	@printf "$(RED)$(NAME) removed$(RESET)\n"
	@printf "$(MAGENTA)"

re: fclean all

.PHONY: all clean fclean re bonus
