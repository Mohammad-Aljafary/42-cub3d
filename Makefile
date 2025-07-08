include src.mk

NAME = cub3D
CC = cc
CFLAGS = -Wall -Wextra -Werror -g $(INCLUDE)
LIBFT = ./libft
LIBFT_A = $(LIBFT)/libft.a
MLX = ./MLX42
MLX_A = $(MLX)/build/libmlx42.a
MLX_FLAGS = -L$(MLX)/build -lglfw -lm -lpthread -ldl -lrt
SRC_DIR = src
OBJ_DIR = objs
INCLUDE = -I$(LIBFT)/includes -I$(MLX)/include -I./include
SRC_FILES = $(addprefix $(SRC_DIR)/, $(SRC))
OBJ_FILES = $(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))

all: $(NAME)

$(NAME): $(OBJ_FILES) $(LIBFT_A) $(MLX_A)
	$(CC) $(CFLAGS) -o $@ $^ $(MLX_FLAGS)

$(LIBFT_A):
	$(MAKE) -C $(LIBFT)

$(MLX_A):
	cmake -B $(MLX)/build $(MLX); \
	cmake --build $(MLX)/build -j4

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(MAKE) -C $(LIBFT) clean
	@if [ -d "$(MLX)/build" ]; then \
		echo "Cleaning MLX42 build..."; \
		cmake --build $(MLX)/build --target clean; \
	fi
	rm -rf $(OBJ_DIR)

fclean: clean
	$(MAKE) -C $(LIBFT) fclean
	@if [ -d "$(MLX)/build" ]; then \
		echo "Removing MLX42 build directory..."; \
		rm -rf $(MLX)/build; \
	fi
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
