NAME := miniRT
OUT_DIR := /tmp

.PHONY: all clean fclean test check
all:
	@echo "all"
	@echo "#!/usr/bin/env bash" > $(OUT_DIR)/miniRT
	@echo "echo hello" >> $(OUT_DIR)/miniRT
	@chmod +x $(OUT_DIR)/miniRT

clean:
	@echo "clean"

fclean:
	@echo "fclean"

test:
	@echo "test"

check:
	@echo "check"
