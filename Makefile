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
SRCS        := $(shell find $(SRC_DIR) -name "*.c" 2>/dev/null)
OBJS        := $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRCS))

# BONUS - busca recursivamente en src_bonus/
SRCS_BONUS  := $(shell find $(SRC_BONUS) -name "*.c" 2>/dev/null)
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
	@echo "$(GREEN)🔨 Compiling $< (bonus)...$(RESET)"
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