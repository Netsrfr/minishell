#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jpfeffer <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/04/24 17:50:14 by jpfeffer          #+#    #+#              #
#    Updated: 2017/04/24 17:58:15 by jpfeffer         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

1SH = minishell

C_FILES = minishell.c utility.c persist.c environ.c exec.c

LIBFT		=	./libft/libft.a
PRINTF		=	./libraries/ft_printf/libftprintf.a
GNL			=	./libraries/get_next_line/libgnl.a
LIBLINK		=	-L ./libraries -lminishell
LIBRARY		=	./libraries/libminishell.a

SRCS = $(C_FILES)

C_FLAGS = -Wall -Werror -Wextra

.PHONY: all library libft printf gnl test testre clean fclean re

all: library $(1SH)

library: libft printf gnl $(LIBRARY)

$(LIBRARY):
	@libtool -static -o ./libraries/libminishell.a $(LIBFT) $(PRINTF) $(GNL)

libft: $(LIBFT)

$(LIBFT):
	@make -C ./libft

printf: $(PRINTF)

$(PRINTF):
	@make -C ./libraries/ft_printf

gnl: $(GNL)

$(GNL):
	@make -C ./libraries/get_next_line

$(1SH): $(C_FILES) minishell.h
	@gcc $(C_FLAGS) $(LIBLINK) $(SRCS) -o minishell

test: library
	@gcc $(SRCS) -lncurses $(LIBLINK) -o minishell

testre: fclean library
	@gcc $(SRCS) -lncurses $(LIBLINK) -o minishell

ftest: fclean library
	@gcc $(SRCS) $(LIBLINK) -fsanitize=address -o minishell

clean:
	@make clean -C ./libft
	@make clean -C ./libraries/ft_printf
	@make clean -C ./libraries/get_next_line

fclean: clean
	@rm -f $(LIBRARY) a.out minishell
	@make fclean -C ./libft
	@make fclean -C ./libraries/ft_printf
	@make fclean -C ./libraries/get_next_line

re: fclean all