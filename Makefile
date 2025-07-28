# ディレクトリ設定
OUT_DIR := $(shell pwd)
ifneq ($(shell echo -n $$IN_DOCKER),)
	OUT_DIR := /tmp/miniRT
endif
OBJ_DIR := $(OUT_DIR)/obj
SRC_DIR := ./src
INC_DIR := ./include
LIBFT_DIR := ./libft

# ファイル
NAME := $(OUT_DIR)/miniRT
SRC := $(addprefix $(SRC_DIR)/, \
	main.c \
)
OBJ := $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC))
INC := $(addprefix $(INC_DIR)/, \
	$(addprefix minirt/, \
		minirt.h \
	) \
)

# ライブラリ
LIBFT = $(OUT_DIR)/libft/libft.a

# コンパイル方法
.DEFAULT_GOAL := all
CC := gcc
# CC := cc
CFLAGS := -Wall -Wextra -Werror -ggdb3
INCFLAGS := $(addprefix -I, \
	$(INC_DIR) \
	$(LIBFT_DIR)/$(INC_DIR) \
)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(INC)
	mkdir -p $(@D)
	$(CC) $(CFLAGS) $(INCFLAGS) -c $< -o $@

$(NAME): $(OBJ) $(LIBFT)
	$(CC) $(CFLAGS) $(INCFLAGS) $(OBJ) $(LIBFT) -o $(NAME)

$(LIBFT):
	make --directory=$(LIBFT_DIR) --no-print-directory OUT_DIR=$(OUT_DIR)/libft all

# 必須ルール
.PHONY: all clean fclean re
all: $(NAME)

clean:
	make --directory=$(LIBFT_DIR) --no-print-directory OUT_DIR=$(OUT_DIR)/libft clean
	$(RM) -r $(OBJ_DIR)

fclean:
	make --directory=$(LIBFT_DIR) --no-print-directory OUT_DIR=$(OUT_DIR)/libft fclean
	$(RM) -r $(OBJ_DIR)
	$(RM) $(NAME)

re: fclean all

# テストルール
.PHONY: test check
test:
	@echo "test"

check:
	@echo "check"

# docker 関連ルール
docker-check:
	@docker image build --tag minirt-check --target check .
	@docker container run \
		--rm \
		--interactive \
		--tty \
		minirt-check

docker-build:
	@docker image build --tag minirt-build --target build .
	@docker container run \
		--rm \
		--interactive \
		--tty \
		minirt-build

docker-test:
	@docker image build --tag minirt-test --target test .
	@docker container run \
		--rm \
		--interactive \
		--tty \
		minirt-test

docker-dev:
	@docker image build --tag minirt-dev --target dev .
	@docker container run \
		--rm \
		--interactive \
		--tty \
		--mount type=bind,source=.,target=/src \
		minirt-dev \

docker-run:
	@docker image build --tag minirt --target final .
	@docker container run \
		--rm \
		--interactive \
		--tty \
		minirt
