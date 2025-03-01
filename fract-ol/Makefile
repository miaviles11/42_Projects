NAME = fractol

SRCS =	src/main.c \
		src/events.c \
		src/mandelbrot.c \
		src/julia.c \

OBJS = $(SRCS:.c=.o)

CC = cc
CFLAGS = -Wall -Werror -Wextra -Iinclude -Iminilibx-linux -Ilibft
LIBS = -Lminilibx-linux -lmlx -lXext -lX11 -lm -Llibft -lft

all: libft minilib $(NAME)

libft:
	@echo "Compilando libft..."
	$(MAKE) -C libft

minilib:
	@echo "Compilando minilibx-linux..."
	$(MAKE) -C minilibx-linux

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)
	$(MAKE) -C libft clean
	$(MAKE) -C minilibx-linux clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C libft fclean

re: fclean all

.PHONY: all clean fclean re libft minilib