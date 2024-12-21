# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: miaviles <miaviles@student.42madrid>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/17 16:50:34 by miaviles          #+#    #+#              #
#    Updated: 2024/12/17 20:46:48 by miaviles         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME_CLIENT = client
NAME_SERVER = server

# Compiler settings
CC = cc
CFLAGS = -Wall -Wextra -Werror -g
INCLUDES = -I include -I libft/include -I libft/ft_printf/include
LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a
PRINTF = $(LIBFT_DIR)/libftprintf.a

# Color codes
RESET = \033[0m
RED = \033[0;31m
GREEN = \033[0;32m

# Source files for minitalk
CLIENT_SRC = src/client.c
SERVER_SRC = src/server.c

# Object files
CLIENT_OBJS = $(CLIENT_SRC:.c=.o)
SERVER_OBJS = $(SERVER_SRC:.c=.o)

# Main target
all: $(LIBFT) $(PRINTF) client server

# Compile libft
$(LIBFT) $(PRINTF):
		@echo "$(GREEN)Compiling libft and ft_printf..$(RESET)"
		@$(MAKE) -C $(LIBFT_DIR)

# Compile client
client: $(CLIENT_OBJS) $(LIBFT) $(PRINTF)
		@echo "$(GREEN)Compiling client...$(RESET)"
		$(CC) $(CFLAGS) $(INCLUDES) $(CLIENT_OBJS) -L$(LIBFT_DIR) -lftprintf -lft -o $(NAME_CLIENT)
		@echo "$(GREEN)Client compile successfully$(RESET)"

# Compile server
server: $(SERVER_OBJS) $(LIBFT) $(PRINTF)
			@echo "$(GREEN)Compiling server...$(RESET)"
			$(CC) $(CFLAGS) $(INCLUDES) $(SERVER_OBJS) -L$(LIBFT_DIR) -lftprintf -lft -o $(NAME_SERVER)
			@echo "$(GREEN)Server compiled successfully$(RESET)"

# Compile individual object files
%.o: %.c
		$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Clean object files
clean:
		@echo "$(RED)Removing executables...$(RESET)"
		@rm -f $(CLIENT_OBJS) $(SERVER_OBJS)
		@$(MAKE) -C $(LIBFT_DIR) clean
		@echo "$(GREEN)Removed successfully..$(RESET)"

# Remove executables and object files
fclean:
		@echo "$(RED)Removing executables..$(RESET)"
		@rm -f $(NAME_CLIENT) $(NAME_SERVER) $(CLIENT_OBJS) $(SERVER_OBJS)
		@$(MAKE) -C $(LIBFT_DIR) fclean
		@echo "$(GREEN)Removed successfully..$(RESET)"

# Rebuilding everything
re: fclean all

.PHONY: all clean fclean re