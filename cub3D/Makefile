# **************************************************************************** #
#                                   cub3D                                      #
# **************************************************************************** #

NAME        := cub3D
NAME_BONUS  := cub3D_bonus

# ============================================================================ #
#                               DIRECTORIOS                                    #
# ============================================================================ #

SRC_DIR     := src
SRC_BONUS   := src_bonus
INC_DIR     := include
INC_BONUS   := include_bonus
OBJ_DIR     := obj
OBJ_BONUS   := obj_bonus

LIBFT_DIR   := libft
MLX_DIR     := minilibx-linux

# ============================================================================ #
#                            COMPILADOR Y FLAGS                                #
# ============================================================================ #

CC          := cc
CFLAGS      := -Wall -Wextra -Werror -g
CFLAGS      += -fno-pie
LDFLAGS     := -no-pie

# FLAGS específicos para MANDATORY (usa include/)
CFLAGS_MAND := $(CFLAGS) -I$(INC_DIR) -I$(LIBFT_DIR) -I$(MLX_DIR)

# FLAGS específicos para BONUS (usa include_bonus/)
CFLAGS_BONUS := $(CFLAGS) -I$(INC_BONUS) -I$(LIBFT_DIR) -I$(MLX_DIR)

# ============================================================================ #
#                                LIBRERÍAS                                     #
# ============================================================================ #

LIBFT       := $(LIBFT_DIR)/libft.a
MLX_LIB     := $(MLX_DIR)/libmlx_Linux.a
LIBS        := -lX11 -lXext -lm -lz

# ============================================================================ #
#                            ARCHIVOS FUENTE                                   #
# ============================================================================ #

# MANDATORY - busca recursivamente en src/
SRCS        := 		src/core/cleanup.c \
					src/core/core_utils.c \
					src/core/loop.c \
					src/core/run.c \
					src/core/timing.c \
					src/events/exit_program.c \
					src/events/hooks.c \
					src/events/key_press.c \
					src/events/key_release.c \
					src/init/init_map.c \
					src/init/init_mlx.c \
					src/init/init_player.c \
					src/init/init_textures.c \
					src/init/init_utils.c \
					src/init/init_utils_2.c \
					src/parse/normalize_map.c \
					src/parse/parse_colors.c \
					src/parse/parse_identifiers.c \
					src/parse/process_meta_helpers.c \
					src/parse/check_map.c \
					src/parse/check_map_utils.c \
					src/parse/parse_utils.c \
					src/parse/parser.c \
					src/physics/movement.c \
					src/physics/movement_collision.c \
					src/physics/movement_sliding.c \
					src/physics/movement_subdiv.c \
					src/physics/movement_utils.c \
					src/render/draw_floor_ceil.c \
					src/render/draw_walls.c \
					src/render/raycaster.c \
					src/render/raycaster_utils.c \
					src/render/texture_sampling.c \
					src/utils/error.c \
					src/utils/free_arr.c \
					src/utils/math.c \
					src/utils/mlx_custom.c \
					src/utils/path_utils.c \
					src/utils/vector.c \
					src/main.c \
					
OBJS        := $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRCS))

# BONUS - busca recursivamente en src_bonus/
SRCS_BONUS  := 		src_bonus/bonus/events/mouse_bonus.c \
					src_bonus/bonus/physics/doors_physics_bonus.c \
					src_bonus/bonus/physics/sprite_collision_bonus.c \
					src_bonus/bonus/render/crosshair_bonus.c \
					src_bonus/bonus/render/doors_parse_bonus.c \
					src_bonus/bonus/render/minimap_bonus.c \
					src_bonus/bonus/render/minimap_colors.c \
					src_bonus/bonus/render/minimap_player_bonus.c \
					src_bonus/bonus/render/sprites_draw_bonus.c \
					src_bonus/bonus/render/sprites_load.c \
					src_bonus/bonus/render/sprites_load_utils.c \
					src_bonus/bonus/render/sprites_parse_bonus.c \
					src_bonus/bonus/render/sprites_render_bonus.c \
					src_bonus/bonus/render/sprites_render_utils_bonus.c \
					src_bonus/bonus/render/texture_manager.c \
					src_bonus/bonus/shooter/shoot.c \
					src_bonus/bonus/shooter/shoot_utils.c \
					src_bonus/bonus/shooter/weapon.c \
					src_bonus/bonus/shooter/weapon_utils.c \
					src_bonus/core/victory_display.c \
					src_bonus/core/victory_display_utils.c \
					src_bonus/core/cleanup.c \
					src_bonus/core/cleanup_utils.c \
					src_bonus/core/core_utils.c \
					src_bonus/core/loop.c \
					src_bonus/core/run.c \
					src_bonus/core/timing.c \
					src_bonus/events/exit_program.c \
					src_bonus/events/key_press.c \
					src_bonus/events/key_release.c \
					src_bonus/init/init_map.c \
					src_bonus/init/init_map_utils.c \
					src_bonus/init/init_mlx.c \
					src_bonus/init/init_player.c \
					src_bonus/init/init_textures.c \
					src_bonus/init/init_textures_utils_1.c \
					src_bonus/init/init_textures_utils_2.c \
					src_bonus/parse/check_map.c \
					src_bonus/parse/check_map_utils.c \
					src_bonus/parse/normalize_map.c \
					src_bonus/parse/parse_colors.c \
					src_bonus/parse/parse_identifiers.c \
					src_bonus/parse/parse_utils.c \
					src_bonus/parse/parser.c \
					src_bonus/parse/process_meta_helpers.c \
					src_bonus/physics/movement_collision.c \
					src_bonus/physics/movement_jump.c \
					src_bonus/physics/movement_sliding.c \
					src_bonus/physics/movement.c \
					src_bonus/physics/movement_subdiv.c \
					src_bonus/physics/movement_utils.c \
					src_bonus/render/draw_floor_ceil.c \
					src_bonus/render/draw_walls.c \
					src_bonus/render/raycaster.c \
					src_bonus/render/raycaster_utils.c \
					src_bonus/render/texture_sampling.c \
					src_bonus/utils/cub_error.c \
					src_bonus/utils/free_arr.c \
					src_bonus/utils/math_utils.c \
					src_bonus/utils/mlx_custom.c \
					src_bonus/utils/path_utils.c \
					src_bonus/utils/vector_ops.c \
					src_bonus/main.c \
					
OBJS_BONUS  := $(patsubst $(SRC_BONUS)/%.c,$(OBJ_BONUS)/%.o,$(SRCS_BONUS))

# ============================================================================ #
#                                COLORES                                       #
# ============================================================================ #

GREEN  := \033[0;32m
BLUE   := \033[0;34m
YELLOW := \033[0;33m
RED    := \033[0;31m
RESET  := \033[0m

# ============================================================================ #
#                           REGLA PRINCIPAL (MANDATORY)                        #
# ============================================================================ #

all: $(NAME)

$(NAME): $(LIBFT) $(MLX_LIB) $(OBJ_DIR) $(OBJS)
	@echo "$(BLUE)🔗 Linking $(NAME) (mandatory)...$(RESET)"
	@$(CC) $(CFLAGS_MAND) $(LDFLAGS) $(OBJS) $(LIBFT) $(MLX_LIB) $(LIBS) -o $(NAME)
	@echo "$(GREEN)✅ $(NAME) compiled successfully!$(RESET)"
	@echo "$(GREEN)   Run: ./$(NAME) assets/maps/map.cub$(RESET)"

# ============================================================================ #
#                              REGLA BONUS                                     #
# ============================================================================ #

bonus: $(NAME_BONUS)

$(NAME_BONUS): $(LIBFT) $(MLX_LIB) $(OBJ_BONUS) $(OBJS_BONUS)
	@echo "$(BLUE)🔗 Linking $(NAME_BONUS)...$(RESET)"
	@$(CC) $(CFLAGS_BONUS) $(LDFLAGS) $(OBJS_BONUS) $(LIBFT) $(MLX_LIB) $(LIBS) -o $(NAME_BONUS)
	@echo "$(GREEN)✅ $(NAME_BONUS) compiled with bonus features!$(RESET)"
	@echo "$(GREEN)   Features: sprites, minimap, mouse, weapon$(RESET)"
	@echo "$(GREEN)   Run: ./$(NAME_BONUS) assets/maps/map.cub$(RESET)"

# ============================================================================ #
#                          COMPILAR LIBFT                                      #
# ============================================================================ #

$(LIBFT):
	@echo "$(YELLOW)📚 Compiling libft...$(RESET)"
	@$(MAKE) -C $(LIBFT_DIR) bonus CFLAGS="-Wall -Wextra -Werror -g" --no-print-directory

# ============================================================================ #
#                          COMPILAR MINILIBX                                   #
# ============================================================================ #

$(MLX_LIB):
	@echo "$(YELLOW)🖼️  Compiling MiniLibX...$(RESET)"
	@$(MAKE) -C $(MLX_DIR) --no-print-directory

# ============================================================================ #
#                       CREAR DIRECTORIOS DE OBJETOS                           #
# ============================================================================ #

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(OBJ_BONUS):
	@mkdir -p $(OBJ_BONUS)

# ============================================================================ #
#                      COMPILAR OBJETOS MANDATORY                              #
# ============================================================================ #

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	@mkdir -p $$(dirname $@)
	@echo "$(GREEN)🔨 Compiling $<...$(RESET)"
	@$(CC) $(CFLAGS_MAND) -c $< -o $@

# ============================================================================ #
#                       COMPILAR OBJETOS BONUS                                 #
# ============================================================================ #

$(OBJ_BONUS)/%.o: $(SRC_BONUS)/%.c | $(OBJ_BONUS)
	@mkdir -p $$(dirname $@)
	@echo "$(GREEN)🔨 Compiling $< \$(RESET)"
	@$(CC) $(CFLAGS_BONUS) -c $< -o $@

# ============================================================================ #
#                               LIMPIEZA                                       #
# ============================================================================ #

clean:
	@echo "$(YELLOW)🧹 Cleaning object files...$(RESET)"
	@$(RM) -r $(OBJ_DIR) $(OBJ_BONUS)
	@$(MAKE) -C $(LIBFT_DIR) clean --no-print-directory
	@$(MAKE) -C $(MLX_DIR) clean --no-print-directory
	@echo "$(GREEN)✓ Object files cleaned$(RESET)"

fclean: clean
	@echo "$(YELLOW)🧹 Cleaning executables...$(RESET)"
	@$(RM) $(NAME) $(NAME_BONUS)
	@$(MAKE) -C $(LIBFT_DIR) fclean --no-print-directory
	@echo "$(GREEN)✓ Executables cleaned$(RESET)"

re: fclean all

re_bonus: fclean bonus

# ============================================================================ #
#                                 HELP                                         #
# ============================================================================ #

help:
	@echo "$(BLUE)╔════════════════════════════════════════════════════════════════╗$(RESET)"
	@echo "$(BLUE)║                       cub3D Makefile                           ║$(RESET)"
	@echo "$(BLUE)╚════════════════════════════════════════════════════════════════╝$(RESET)"
	@echo ""
	@echo "$(GREEN)Available targets:$(RESET)"
	@echo ""
	@echo "  $(YELLOW)make$(RESET)           - Compile mandatory version (./$(NAME))"
	@echo "  $(YELLOW)make bonus$(RESET)     - Compile bonus version (./$(NAME_BONUS))"
	@echo "  $(YELLOW)make clean$(RESET)     - Remove object files"
	@echo "  $(YELLOW)make fclean$(RESET)    - Remove object files and executables"
	@echo "  $(YELLOW)make re$(RESET)        - Recompile mandatory"
	@echo "  $(YELLOW)make re_bonus$(RESET)  - Recompile bonus"
	@echo "  $(YELLOW)make debug$(RESET)     - Show project structure and files"
	@echo "  $(YELLOW)make help$(RESET)      - Show this help message"
	@echo ""
	@echo "$(GREEN)Usage:$(RESET)"
	@echo "  ./$(NAME) maps/map.cub          - Run mandatory"
	@echo "  ./$(NAME_BONUS) maps/map.cub    - Run bonus"
	@echo ""

# ============================================================================ #
#                                PHONY                                         #
# ============================================================================ #

.PHONY: all bonus clean fclean re re_bonus help