NAME := miniRT

# ディレクトリ設定
OUT_DIR := .
ifneq ($(shell echo -n $$IN_DOCKER),)
	OUT_DIR := /tmp
endif
OBJ_DIR := $(OUT_DIR)/obj
SRC_DIR := ./src
INC_DIR := ./include

# ファイル
SRC := $(addprefix $(SRC_DIR)/, \
	main.c \
)
OBJ := $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC))
INC := $(addprefix $(INC_DIR)/, \
	$(addprefix minirt/, \
		minirt.h \
	) \
)

# コンパイル方法
CC := gcc
# CC := cc
CFLAGS := -Wall -Wextra -Werror -ggdb3
INCFLAGS := $(addprefix -I, \
	$(INC_DIR) \
)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(INC)
	mkdir -p $(@D)
	$(CC) $(CFLAGS) $(INCFLAGS) -c $< -o $@

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(INCFLAGS) $(OBJ) -o $(NAME)


# 必須ルール
.PHONY: all clean fclean re
all: $(NAME)

clean:
	$(RM) -r $(OBJ_DIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all

# テストルール
.PHONY: test check
test:
	@echo "test"

check:
	@echo "check"
