NAME := miniRT
OUT_DIR := .
ifneq ($(shell echo -n $$IN_DOCKER),)
	OUT_DIR := /tmp
endif

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
