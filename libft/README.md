# Libft

This repository contains my personal implementation of Libft, a project that is part of the 42 curriculum. Libft is a library of useful functions that I will be using throughout my 42 journey.

## Project Overview

The goal of this project is to create our own library with useful functions that we can use in our future projects. This project is a great opportunity to consolidate our understanding of some of the fundamental concepts in C programming, such as memory management, pointers, and data structures.

## Features

The library includes a wide range of functions/types, including but not limited to:

- String manipulation
- Linked list manipulation
- Vec/Array manipulation
- Memory allocation and management
- Input/Output functions
- String formatting functions

## Extension

This library is designed to be easily extendable. As I progress through the 42 curriculum, I will be adding more functions that I find useful.

## Usage

To use this library in your project, simply include a clone of this repository and modify your Makefile to make and include the libft.a file when making.

```Makefile
NAME = my_program
CC = gcc
CFLAGS = -Wall -Wextra -Werror
SRC = main.c
OBJ = $(SRC:.c=.o)
LIBFT = libft/libft.a

all: $(NAME)

$(NAME): $(OBJ)
	$(MAKE) -C libft
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(LIBFT)
```

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.
