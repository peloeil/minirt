# 出力の設定
ESC := $(shell printf "\033")
END := $(ESC)[m
BRIGHT_RED := $(ESC)[91m
BRIGHT_GREEN := $(ESC)[92m
BRIGHT_CYAN := $(ESC)[96m
CLEAR := $(ESC)[K

# ディレクトリ設定
OUT_DIR := $(CURDIR)
OBJ_DIR := $(OUT_DIR)/obj
SRC_DIR := ./src
INC_DIR := ./include
LIBFT_DIR := ./libft
MLX_DIR := $(OUT_DIR)/mlx_linux
TEST_DIR := ./test

# ファイル
NAME := $(OUT_DIR)/miniRT
SRC_TEST := $(addprefix $(SRC_DIR)/, \
	$(addprefix vec3/, \
		vec3_util1.c \
		vec3_util2.c \
	) \
	$(addprefix scene/, \
		scene.c \
	) \
	$(addprefix ray_tracing/, \
		ray_tracing.c \
		core.c \
		plane.c \
		sphere.c \
		cylinder.c \
		$(addprefix reflection/, \
			phong_reflection.c \
		) \
	) \
	$(addprefix parser/, \
		parser.c \
		assign.c \
		ambient_light.c \
		camera.c \
		light.c \
		sphere.c \
		plane.c \
		cylinder.c \
		parse_rt_line.c \
		parse_double.c \
		parse_vec3.c \
		parse_color.c \
		free.c \
		exit.c \
	) \
	$(addprefix mlx_api/, \
		lifecycle.c \
		event.c \
		img_pixel.c \
	) \
	$(addprefix renderer/, \
		renderer.c \
	) \
)
SRC := $(SRC_TEST) $(SRC_DIR)/main.c
OBJ_TEST := $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC_TEST))
OBJ := $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC))
DEPEND := $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.d, $(SRC))
INC := $(addprefix $(INC_DIR)/, \
	$(addprefix minirt/, \
		vec3.h \
		scene.h \
		parser.h \
		ray_tracing.h \
		mlx_api.h \
		renderer.h \
	) \
)
TEST := $(patsubst $(SRC_DIR)/%, $(TEST_DIR)/%, $(SRC_TEST))
NUM_FILES := $(words $(SRC))

# ライブラリ
LIBFT := $(OUT_DIR)/libft/libft.a
MLX := $(MLX_DIR)/libmlx_Linux.a
LIB := $(LIBFT) $(MLX)

# コンパイル方法
.DEFAULT_GOAL := all
CC := cc
CFLAGS := -Wall -Wextra -Werror -MMD -MP
MLXFLAGS := -lX11 -lXext -lm
INCFLAGS := $(addprefix -I, \
	$(INC_DIR) \
	$(LIBFT_DIR)/$(INC_DIR) \
	$(MLX_DIR) \
)

-include $(DEPEND)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(@D)
	@printf \
		"\r$(CLEAR)%-15s: [%2d/%2d] $(BRIGHT_GREEN)compiling $(BRIGHT_CYAN)%s$(END)" \
		$(shell basename $(NAME)) \
		$(shell echo "$(SRC)" | tr " " "\n" | grep -n "$<" | cut -d : -f 1) \
		$(NUM_FILES) \
		$(shell echo $< | sed 's|$(SRC_DIR)/||g')
	@-$(CC) $(CFLAGS) $(INCFLAGS) -c $< -o $@

$(NAME): $(LIB) $(OBJ)
	@printf \
		"\r$(CLEAR)%-15s: $(BRIGHT_GREEN)compilation finished$(END)\n" \
		$(shell basename $(NAME))
	@$(CC) $(CFLAGS) $(OBJ) $(LIB) $(MLXFLAGS) -o $(NAME)
	@printf "%-15s: create $(NAME)\n" $(shell basename $(NAME))

$(LIBFT):
	@$(MAKE) --directory=$(LIBFT_DIR) --no-print-directory OUT_DIR="$(OUT_DIR)/libft" CC="$(CC)" all

$(MLX): | $(MLX_DIR)
	@$(MAKE) --directory=$(MLX_DIR) --no-print-directory all >/dev/null
	@printf "%-15s: create $(MLX)\n" $(shell basename $(NAME))

$(MLX_DIR):
	@git clone https://github.com/42paris/minilibx-linux.git $(MLX_DIR)

# 必須ルール
.PHONY: all clean fclean re
all: $(NAME)

clean: | $(MLX_DIR)
	@$(RM) -r $(OBJ_DIR)
	@printf "%-15s: remove $(OBJ_DIR)\n" $(shell basename $(NAME))
	@$(MAKE) --directory=$(LIBFT_DIR) --no-print-directory OUT_DIR=$(OUT_DIR)/libft clean
	@-$(MAKE) --directory=$(MLX_DIR) --no-print-directory clean
	@printf "%-15s: remove $(MLX_DIR)\n" $(shell basename $(NAME))

fclean: | $(MLX_DIR)
	@$(RM) -r $(OBJ_DIR)
	@printf "%-15s: remove $(OBJ_DIR)\n" $(shell basename $(NAME))
	@$(RM) $(NAME)
	@printf "%-15s: remove $(NAME)\n" $(shell basename $(NAME))
	@$(MAKE) --directory=$(LIBFT_DIR) --no-print-directory OUT_DIR=$(OUT_DIR)/libft fclean
	@-$(MAKE) --directory=$(MLX_DIR) --no-print-directory clean
	@printf "%-15s: remove $(MLX_DIR)\n" $(shell basename $(NAME))

re: fclean all
