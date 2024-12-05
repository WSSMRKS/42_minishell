# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sgramsch <sgramsch@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/29 15:15:58 by zblume            #+#    #+#              #
#    Updated: 2024/12/05 12:34:00 by sgramsch         ###   ########.fr        #
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
FLAGS = -Wall -Wextra -Werror
RL = -lreadline -lncurses
OPTIONS = -c

SRC_DIR = ./src

SRC = $(addprefix $(SRC_DIR)/,\
	cleanup_structs.c		\
	cleanup.c				\
	data_var.c 				\
	env_expanding.c 		\
	env_helpers.c			\
	error_handling.c		\
	exec.c					\
	execute_cd.c			\
	execute_env.c			\
	execute_exit.c 			\
	execute_export.c		\
	execute.c				\
	fd_handling.c			\
	helpers.c 				\
	input_setup.c			\
	lst_cmd.c				\
	lst_env.c				\
	lst_token.c 			\
	main.c					\
	redirect_heredoc.c		\
	redirect_name.c 		\
	redirect_new.c			\
	redirection_helpers.c	\
	redirections.c			\
	signal_heredoc.c		\
	signal.c				\
	subshell.c				\
	token_assign.c 			\
	token.c 				\
	tokenize_red.c 			)

INCLUDES = inc/minishell.h

OBJ_DIR = ./obj
OBJ = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRC))

LIBFT_DIR = libft
LIBFT = libft.a
LIBFT_SRC = $(shell find $(LIBFT_DIR) -name "*.c")

NAME = minishell

all:  $(LIBFT_DIR)/$(LIBFT) $(NAME)

$(NAME): $(OBJ)
	@echo "$(GREEN)Compiling $(NAME)... $(RESET)"
	@$(CC) $(FLAGS) $(OBJ) $(LIBFT_DIR)/$(LIBFT) $(RL) -o $(NAME)

$(LIBFT_DIR)/$(LIBFT): $(LIBFT_SRC)
	@echo "$(GREEN)Building $(LIBFT)... $(RESET)"
	@make -s -C $(LIBFT_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(INCLUDES)
	@mkdir -p $(OBJ_DIR)
	@$(CC) -g $(FLAGS) $(OPTIONS) $< -o $@
	@echo "$(BLUE)Compiling... $(CYAN)$<$(RESET)"

clean:
	@printf "$(MAGENTA)"
	@make clean -s -C $(LIBFT_DIR)
	@echo "$(RED)Deleting Objects... $(RESET)"
	@rm -rf $(OBJ_DIR)
	@printf "$(RESET)"

fclean: clean
	@printf "$(MAGENTA)"
	@make fclean -C $(LIBFT_DIR)
	@echo "$(RED)Deleting $(NAME)... $(RESET)"
	@rm -f $(NAME)
	@printf "$(RESET)"

re: fclean all

.PHONY: all re clean fclean libs debug
