NAME		= minishell

CC			= cc
CFLAGS		= -Wall -Wextra -Werror -g

LIBFT_DIR	= libft
LIBFT		= $(LIBFT_DIR)/libft.a

SRCS		=	src/builtins/builtins_utils_export.c \
				src/builtins/builtins_utils.c \
				src/builtins/ft_cd.c \
				src/builtins/ft_echo.c \
				src/builtins/ft_env.c \
				src/builtins/ft_exit.c \
				src/builtins/ft_export.c \
				src/builtins/ft_pwd.c \
				src/builtins/ft_unset.c \
				src/executor/child_process.c \
				src/executor/exec_builtin.c \
				src/executor/exec_utils_builtin.c \
				src/executor/exec_utils.c \
				src/executor/exec_utils_2.c \
				src/executor/executor_heredoc.c \
				src/executor/executor_pipe.c \
				src/executor/executor_pipe_utils.c \
				src/executor/executor.c \
				src/parser/create_command_node/process_arguments_1.c \
				src/parser/create_command_node/process_arguments_2.c \
				src/parser/create_command_node/process_arguments_3.c \
				src/parser/create_command_node/process_arguments_utils.c \
				src/parser/perform_expansion/variable_braced.c \
				src/parser/perform_expansion/variable_detection.c \
				src/parser/perform_expansion/variable_env.c \
				src/parser/perform_expansion/variable_expansion.c \
				src/parser/perform_expansion/variable_processing.c \
				src/parser/perform_expansion/variable_substitution.c \
				src/parser/validate_input/p_pipes_redir.c \
				src/parser/validate_input/p_pipes_utils.c \
				src/parser/validate_input/parse_pipes.c \
				src/parser/validate_input/parse_quotes.c \
				src/parser/parser.c \
				src/parser/parser_functions.c \
				src/signals/signals.c \
				src/shell/clean_minishell.c \
				src/shell/ft_error.c \
				src/shell/env_setter.c \
				src/shell/env_utils.c \
				src/shell/init_shell.c \
				src/shell/shell_level.c \
				src/minishell.c \
				src/shell_loop.c \
				utils/utils_1.c \
				utils/redir_utils2.c \
				utils/exec_utils.c \
				utils/redir_utils.c \
				src/redirections/redirect_heredoc.c \
				src/redirections/redirect.c \
				src/redirections/redirection_utils_1.c \
				src/redirections/redirection_utils_2.c \
				src/redirections/redirection_utils_3.c \

OBJS		= $(SRCS:.c=.o)

RM			= rm -f

INCLUDES	= -I includes

GREEN		= \033[0;32m
YELLOW		= \033[0;33m
RED			= \033[0;31m
BLUE		= \033[0;34m
RESET		= \033[0m

all: $(NAME)

$(NAME): $(OBJS)
	@echo "$(YELLOW)Compilando libft...$(RESET)"
	@make -C $(LIBFT_DIR)
	@echo "$(BLUE)Compilando Minishell...$(RESET)"
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -lreadline -o $(NAME)
	@echo "$(GREEN)Minishell compilado con éxito.$(RESET)"

%.o: %.c includes/minishell.h
	@echo "$(BLUE)Compilando $<...$(RESET)"
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	@echo "$(RED)Eliminando archivos objeto...$(RESET)"
	$(RM) $(OBJS)
	@make clean -C $(LIBFT_DIR)

fclean: clean
	@echo "$(RED)Eliminando binario y librería...$(RESET)"
	$(RM) $(NAME)
	@make fclean -C $(LIBFT_DIR)

re: fclean all

.PHONY: all clean fclean re
