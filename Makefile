# **************************************************************************** #
#                                   cub3D                                      #
# **************************************************************************** #

NAME        := cub3D
SRC_DIR     := src
INC_DIR     := include
OBJ_DIR     := obj

LIBFT_DIR   := libft
MLX_DIR     := minilibx-linux

CC          := cc
CFLAGS      := -Wall -Wextra -Werror -g \
               -I$(INC_DIR) -I$(LIBFT_DIR) -I$(MLX_DIR)
# Desactivar PIE en objetos
CFLAGS      += -fno-pie
# Desactivar PIE al enlazar
LDFLAGS     := -no-pie

LIBFT       := $(LIBFT_DIR)/libft.a
MLX_LIB     := $(MLX_DIR)/libmlx_Linux.a
LIBS        := -lX11 -lXext -lm -lz

# Busca recursivamente todos los .c en src/
SRCS        := $(shell find $(SRC_DIR) -name "*.c")
OBJS        := $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRCS))

# ----------------------------------------------------------------------------- #
# Regla principal
# ----------------------------------------------------------------------------- #
all: $(NAME)

$(NAME): $(LIBFT) $(MLX_LIB) $(OBJ_DIR) $(OBJS)
	$(CC) $(CFLAGS) $(LDFLAGS) $(OBJS) $(LIBFT) $(MLX_LIB) $(LIBS) -o $(NAME)

# ----------------------------------------------------------------------------- #
# Compilar libft (incluye get_next_line y bonus)
# ----------------------------------------------------------------------------- #
$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR) bonus CFLAGS="-Wall -Wextra -Werror -g "

# ----------------------------------------------------------------------------- #
# Compilar MiniLibX Linux
# ----------------------------------------------------------------------------- #
$(MLX_LIB):
	@$(MAKE) -C $(MLX_DIR)

# ----------------------------------------------------------------------------- #
# Crear carpeta de objetos
# ----------------------------------------------------------------------------- #
$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

# ----------------------------------------------------------------------------- #
# Compilar cada .c a .o
# ----------------------------------------------------------------------------- #
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	@mkdir -p $$(dirname $@)
	$(CC) $(CFLAGS) -c $< -o $@

# ----------------------------------------------------------------------------- #
# Limpieza
# ----------------------------------------------------------------------------- #
clean:
	$(RM) $(OBJS)
	@$(MAKE) -C $(LIBFT_DIR) clean
	@$(MAKE) -C $(MLX_DIR) clean

fclean: clean
	$(RM) $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

# ----------------------------------------------------------------------------- #
# Phony
# ----------------------------------------------------------------------------- #
.PHONY: all clean fclean re
