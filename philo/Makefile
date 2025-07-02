# Nombre del ejecutable
NAME = philo

# Compilador y flags
CC = cc
CFLAGS = -Wall -Werror -Wextra -MMD -MP

# Archivos fuente y objetos
SRC_DIR = src
SRC = $(wildcard $(SRC_DIR)/*.c)
OBJ = $(SRC:.c=.o)
DEP = $(SRC:.c=.d)

# Colores
GREEN = \033[0;32m
YELLOW = \033[1;33m
BLUE = \033[0;34m
RED = \033[0;31m
NC = \033[0m

# Regla por defecto
all: $(NAME)

# Compilar el ejecutable
$(NAME): $(OBJ)
	@echo "$(YELLOW)[Compilando]$(NC) Generando ejecutable $(NAME)..."
	@$(CC) $(CFLAGS) $(OBJ) -o $(NAME)
	@echo "$(GREEN)[Éxito]$(NC) ¡Compilado correctamente!"

# Regla para compilar .c a .o
%.o: %.c
	@echo "$(BLUE)[Compilando]$(NC) $<"
	@$(CC) $(CFLAGS) -c $< -o $@

# Ejecutar el programa
run: $(NAME)
	@echo "$(GREEN)[Ejecutando]$(NC) ./$(NAME)"
	@./$(NAME)

# Limpiar objetos y dependencias
clean:
	@rm -f $(OBJ) $(DEP)
	@echo "$(RED)[Limpieza]$(NC) Archivos objeto y dependencias eliminados."

# Limpiar todo
fclean: clean
	@rm -f $(NAME)
	@echo "$(RED)[Limpieza total]$(NC) Ejecutable eliminado."

# Reconstruir todo
re: fclean all

# Verificar norma
norm:
	@echo "$(BLUE)[Norminette]$(NC) Revisando includes/ y src/"
	@norminette includes
	@norminette $(SRC)

# Incluir archivos de dependencias generados con -MMD
-include $(DEP)

.PHONY: all clean fclean re norm run
