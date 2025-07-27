NAME := miniRT

# ディレクトリ設定
OUT_DIR := .
ifneq ($(shell echo -n $$IN_DOCKER),)
	OUT_DIR := /tmp
endif
OBJ_DIR := $(OUT_DIR)/obj
SRC_DIR := ./src
INC_DIR := ./include

# 必須ルール
.PHONY: all clean fclean re
all: $(NAME)
	@echo "all"
	@echo "#!/usr/bin/env bash" > $(OUT_DIR)/miniRT
	@echo "echo hello" >> $(OUT_DIR)/miniRT
	@chmod +x $(OUT_DIR)/miniRT

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
