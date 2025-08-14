# 出力の設定
ESC := $(shell printf "\033")
END := $(ESC)[m
RED := $(ESC)[91m
GREEN := $(ESC)[92m

# ディレクトリ設定
OUT_DIR := $(shell pwd)
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
SRC := $(addprefix $(SRC_DIR)/, \
	main.c \
	$(addprefix vec3/, \
		vec3_util1.c \
		vec3_util2.c \
	) \
)
SRC_TEST := $(filter-out $(SRC_DIR)/main.c, $(SRC))
OBJ := $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC))
OBJ_TEST := $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC_TEST))
INC := $(addprefix $(INC_DIR)/, \
	$(addprefix minirt/, \
		minirt.h \
		vec3.h \
	) \
)
TEST := $(patsubst $(SRC_DIR)/%, $(TEST_DIR)/%, $(SRC_TEST))

# ライブラリ
LIBFT := $(OUT_DIR)/libft/libft.a
MLX := $(MLX_DIR)/libmlx_Linux.a
LIB := $(LIBFT) $(MLX)

# コンパイル方法
.DEFAULT_GOAL := all
CC := gcc
# CC := cc
CFLAGS := -Wall -Wextra -Werror -ggdb3
MLXFLAGS := -lX11 -lXext -lm
INCFLAGS := $(addprefix -I, \
	$(INC_DIR) \
	$(LIBFT_DIR)/$(INC_DIR) \
	$(MLX_DIR) \
)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(INC)
	mkdir -p $(@D)
	$(CC) $(CFLAGS) $(INCFLAGS) -c $< -o $@

$(NAME): $(LIB) $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LIB) $(MLXFLAGS) -o $(NAME)

$(LIBFT):
	$(MAKE) --directory=$(LIBFT_DIR) --no-print-directory OUT_DIR=$(OUT_DIR)/libft all

$(MLX): | $(MLX_DIR)
	$(MAKE) --directory=$(MLX_DIR) --no-print-directory all

$(MLX_DIR):
	git clone https://github.com/42paris/minilibx-linux.git $(MLX_DIR)

# 必須ルール
.PHONY: all clean fclean re
all: $(NAME)

clean:
	$(RM) -r $(OBJ_DIR)
	$(MAKE) --directory=$(LIBFT_DIR) --no-print-directory OUT_DIR=$(OUT_DIR)/libft clean
	$(MAKE) --directory=$(MLX_DIR) --no-print-directory clean

fclean:
	$(RM) -r $(OBJ_DIR)
	$(RM) $(NAME)
	$(MAKE) --directory=$(LIBFT_DIR) --no-print-directory OUT_DIR=$(OUT_DIR)/libft fclean
	$(MAKE) --directory=$(MLX_DIR) --no-print-directory clean

re: fclean all

# docker 関連ルール
.PHONY: docker-check docker-build docker-test docker-dev docker-run
docker-check:
	@docker image build --tag minirt-check --target check .

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

# その他のルール
.PHONY: test check format norm lint
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
				printf "$(GREEN)SUCCESS$(END)\n"; \
			else \
				printf "$(RED)FAILED$(END)\n"; \
			fi; \
		fi; \
	done;
	@$(RM) -rf $(OUT_DIR)/out \

check: format norm lint

format: $(SRC)
	c_formatter_42 $(SRC)

norm:
	$(MAKE) --directory=$(LIBFT_DIR) --no-print-directory norm
	norminette $(SRC) $(INC)

lint: compile_commands.json
	if [ -f /.dockerenv ]; then \
		sed -i 's@/home/sota/workspace/42tokyo/minirt@/minirt-src@g' compile_commands.json; \
	fi;
	clang-tidy $(SRC)
	sed -i 's@/minirt-src@/home/sota/workspace/42tokyo/minirt@g' compile_commands.json

compile_commands.json: fclean $(SRC) $(INC)
	bear -- $(MAKE) --no-print-directory all
	compdb list | sponge compile_commands.json
	sed -i 's@/minirt-src@/home/sota/workspace/42tokyo/minirt@g' compile_commands.json
