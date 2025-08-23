# 出力の設定
ESC := $(shell printf "\033")
END := $(ESC)[m
BRIGHT_RED := $(ESC)[91m
BRIGHT_GREEN := $(ESC)[92m
BRIGHT_CYAN := $(ESC)[96m
CLEAR := $(ESC)[K

# ディレクトリ設定
OUT_DIR := $(CURDIR)
ifneq ($(shell echo -n $$IN_DOCKER),)
	OUT_DIR := /tmp/miniRT
endif
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
	$(addprefix ray_tracing/, \
		core.c \
		plane.c \
		sphere.c \
		cylinder.c \
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
CC := gcc
# CC := cc
CFLAGS := -Wall -Wextra -Werror -MMD -MP -Og -ggdb3
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

# docker 関連ルール
.PHONY: docker-check docker-build docker-test docker-dev docker-run
docker-check:
	@docker image build \
		--build-arg HOST_CWD=$(CURDIR) \
		--output=. \
		--progress=plain \
		--tag minirt-check \
		--target check .

docker-build:
	@docker image build --tag minirt-build --target build .

docker-test:
	@docker image build --tag minirt-test --target test .

docker-dev:
	@xhost +local:docker
	@docker image build --tag minirt-dev --target dev .
	@docker container run \
		--rm \
		--interactive \
		--tty \
		--mount type=bind,source=.,target=/minirt-src \
		--mount type=bind,source=/etc/group,target=/etc/group,readonly \
		--mount type=bind,source=/etc/passwd,target=/etc/passwd,readonly \
		--mount type=bind,source=$$HOME/.gitconfig,target=$$HOME/.gitconfig \
		--mount type=bind,source=/tmp/.X11-unix,target=/tmp/.X11-unix \
		--mount type=bind,source=$$HOME/.Xauthority,target=$$HOME/.Xauthority,readonly \
		--env DISPLAY=$$DISPLAY \
		--env HOST_CWD=$$PWD \
		--user $(shell id -u):$(shell id -g) \
		minirt-dev

docker-run:
	@xhost +local:docker
	@docker image build --tag minirt --target final .
	@docker container run \
		--rm \
		--interactive \
		--tty \
		--mount type=bind,source=/etc/group,target=/etc/group,readonly \
		--mount type=bind,source=/etc/passwd,target=/etc/passwd,readonly \
		--mount type=bind,source=/tmp/.X11-unix,target=/tmp/.X11-unix \
		--mount type=bind,source=$$HOME/.Xauthority,target=$$HOME/.Xauthority,readonly \
		--env DISPLAY=$$DISPLAY \
		--user $(shell id -u):$(shell id -g) \
		minirt

# デバッグ関連ルール
.PHONY: debug fortify sanitize
debug: CFLAGS += -fanalyzer
debug: re

fortify: CFLAGS += -O2 -D_FORTIFY_SOURCE=2
fortify: re

sanitize: CFLAGS += -fsanitize=address,leak,undefined
sanitize: re

# その他のルール
.PHONY: test format check norm lint

test: $(LIB) $(OBJ_TEST)
	@echo "------------ test ------------"
	@$(RM) $(OUT_DIR)/result.log
	@mkdir -p $(OUT_DIR)/out
	@for test in $(TEST); do \
		if [ -f $$test ]; then \
			out_file=$(OUT_DIR)/out/$$(basename $$test .c).out; \
			$(CC) $(CFLAGS) $(INCFLAGS) $$test $(OBJ_TEST) $(LIB) $(MLXFLAGS) -o $$out_file; \
			printf "%-30s: " "$$test"; \
			if $$out_file >> $(OUT_DIR)/result.log 2>&1; then \
				printf "$(BRIGHT_GREEN)SUCCESS$(END)\n"; \
			else \
				printf "$(BRIGHT_RED)FAILED$(END)\n"; \
			fi; \
		fi; \
	done;
	@$(RM) -rf $(OUT_DIR)/out

format: $(SRC)
	@c_formatter_42 $(SRC)

check: norm lint

norm:
	@-$(MAKE) --directory=$(LIBFT_DIR) --no-print-directory norm
	@-norminette $(SRC) $(INC)

COMPILE_COMMANDS := $(OUT_DIR)/compile_commands.json
lint:
	@if [ -f /.dockerenv ] || ! [ -n "$$IN_DOCKER" ]; then \
		$(MAKE) $(COMPILE_COMMANDS); \
	fi
	@if [ -f /.dockerenv ] || [ -n "$$IN_DOCKER" ]; then \
		sed -i 's@$(HOST_CWD)@/minirt-src@g' $(COMPILE_COMMANDS); \
	fi
	@-clang-tidy -p $(OUT_DIR) $(SRC)
	@sed -i 's@/minirt-src@$(HOST_CWD)@g' $(COMPILE_COMMANDS)
	@sed -i 's@/tmp/miniRT@$(HOST_CWD)@g' $(COMPILE_COMMANDS)

$(COMPILE_COMMANDS): fclean $(SRC) $(INC)
	@bear --output $(COMPILE_COMMANDS) -- $(MAKE) --no-print-directory all
	@compdb -p $(OUT_DIR) list | sponge $(COMPILE_COMMANDS)
