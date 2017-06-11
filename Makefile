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

NAME = minishell

C_FILES = minishell.c utility.c persist.c environ.c exec.c chdir.c home.c \
helpers.c intro.c bonus.c

LIBFT		=	./libft/libft.a
PRINTF		=	./libraries/ft_printf/libftprintf.a
PRINTE		=	./libraries/ft_printe/libftprinte.a
GNL			=	./libraries/get_next_line/libgnl.a
LIBLINK		=	-L ./libraries -lminishell
LIBRARY		=	./libraries/libminishell.a

SRCS = $(C_FILES)

C_FLAGS = -Wall -Werror -Wextra

.PHONY: all library libft printf printe gnl test testre clean fclean re

all: library $(NAME)

library: libft printf printe gnl $(LIBRARY)

$(LIBRARY):
	@libtool -static -o ./libraries/libminishell.a $(LIBFT) $(PRINTF) \
	$(PRINTE) $(GNL)

libft: $(LIBFT)

$(LIBFT):
	@make -C ./libft

printf: $(PRINTF)

$(PRINTF):
	@make -C ./libraries/ft_printf

printe: $(PRINTE)

$(PRINTE):
	@make -C ./libraries/ft_printe

gnl: $(GNL)

$(GNL):
	@make -C ./libraries/get_next_line

$(NAME): $(C_FILES) minishell.h
	@gcc $(C_FLAGS) $(LIBLINK) $(SRCS) -o minishell

test: library
	@gcc $(SRCS) $(LIBLINK) -o minishell

testre: fclean library
	@gcc $(SRCS) $(LIBLINK) -o minishell

ftest: fclean library
	@gcc $(SRCS) $(LIBLINK) -fsanitize=address -o minishell

clean:
	@make clean -C ./libft
	@make clean -C ./libraries/ft_printf
	@make clean -C ./libraries/ft_printe
	@make clean -C ./libraries/get_next_line

fclean: clean
	@rm -f $(LIBRARY) a.out minishell
	@make fclean -C ./libft
	@make fclean -C ./libraries/ft_printf
	@make fclean -C ./libraries/ft_printe
	@make fclean -C ./libraries/get_next_line

re: fclean all