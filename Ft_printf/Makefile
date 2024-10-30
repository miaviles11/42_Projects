# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: miaviles <miaviles@student.42madrid>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/29 12:42:57 by miaviles          #+#    #+#              #
#    Updated: 2024/10/30 20:31:58 by miaviles         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a

LIBFT_DIR = Libft
LIBFT_OBJ = $(LIBFT_DIR)/*.o

AR = ar -rcs

CC = cc
CFLAGS = -Wall -Werror -Wextra
RN = ranlib

SRC =		ft_printf.c \
			ft_printf_utils.c \
			ft_printf_args.c \

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT_OBJ)
	$(AR) $(NAME) $(OBJ) $(LIBFT_OBJ)
	$(RN) $(NAME)

$(LIBFT_OBJ):
	$(MAKE) -C $(LIBFT_DIR)

%.o: %.c ft_printf.h libft.h
	$(CC) $(CFLAGS) -o $@ $< -c

clean:
	rm -f $(OBJ)
	$(MAKE) clean -C $(LIBFT_DIR)

fclean: clean
	rm -f $(NAME)
	$(MAKE) fclean -C $(LIBFT_DIR)

re: fclean all

.DEFAULT_GOAL: all

.PHONY: all clean fclean re