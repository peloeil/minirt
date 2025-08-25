# 出力の設定
ESC := $(shell printf '\033')
END := $(ESC)[m
CLEAR := $(ESC)[K

BRIGHT_RED := $(ESC)[91m
BRIGHT_GREEN := $(ESC)[92m
BRIGHT_CYAN := $(ESC)[96m

# ディレクトリ設定
OUT_DIR := .
OBJ_DIR := $(OUT_DIR)/obj
SRC_DIR := ./src
INC_DIR := ./include
TEST_DIR := ./test

# ファイル
LIBRARY := libft
NAME := $(OUT_DIR)/$(LIBRARY).a
SRC := $(addprefix $(SRC_DIR)/, \
	$(addprefix ctype/, \
		isalnum.c \
		isalpha.c \
		isascii.c \
		isdigit.c \
		isprint.c \
		isspace.c \
		tolower.c \
		toupper.c \
	) \
	$(addprefix list/, \
		push_back.c \
		push_front.c \
		pop_back.c \
		pop_front.c \
		clear.c \
		delete.c \
		iter.c \
		last.c \
		map.c \
		new.c \
		size.c \
	) \
	$(addprefix stdlib/, \
		atoi.c \
		calloc.c \
		itoa.c \
	) \
	$(addprefix string/, \
		bzero.c \
		memchr.c \
		memcmp.c \
		memcpy.c \
		memmove.c \
		memset.c \
		split.c \
		strchr.c \
		strcmp.c \
		strdup.c \
		striteri.c \
		strjoin.c \
		strlcat.c \
		strlcpy.c \
		strlen.c \
		strmapi.c \
		strncmp.c \
		strndup.c \
		strnstr.c \
		strrchr.c \
		strtrim.c \
		substr.c \
	) \
	$(addprefix std_string/, \
		new.c \
		with_capacity.c \
		from.c \
		reserve.c \
		push.c \
		push_str.c \
		pop.c \
		insert.c \
		starts_with.c \
		ends_with.c \
		find.c \
		rfind.c \
	) \
	$(addprefix stdio/, \
		$(addprefix printf/, \
			push_char.c \
			push_str.c \
			push_int.c \
			push_uint.c \
			push_hex.c \
		) \
		vdprintf.c \
		vprintf.c \
		vsprintf.c \
		vsnprintf.c \
		vasprintf.c \
		dprintf.c \
		printf.c \
		sprintf.c \
		snprintf.c \
		asprintf.c \
		getc.c \
		getdelim.c \
		getline.c \
	) \
)
OBJ := $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC))
INC := $(addprefix $(INC_DIR)/, \
	$(addprefix $(LIBRARY)/, \
		ft_ctype.h \
		ft_list.h \
		ft_stdlib.h \
		ft_stdio.h \
		ft_string.h \
		std_string.h \
	) \
)
TEST := $(patsubst $(SRC_DIR)/%, $(TEST_DIR)/%, $(SRC))
TEST_UTILS := $(addprefix $(TEST_DIR)/, \
	test.c \
)

NUM_FILES := $(words $(SRC))

# コンパイルの設定
CC := cc
CFLAGS := -Wall -Wextra -Werror -fPIE
ARFLAGS := -rcs
INCFLAGS := $(addprefix -I, \
	$(INC_DIR) \
)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(INC)
	@mkdir -p $(@D)
	@printf \
		"\r$(CLEAR)%-15s: [%2d/%2d] $(BRIGHT_GREEN)compiling $(BRIGHT_CYAN)%s$(END)" \
		$(LIBRARY) \
		$(shell echo "$(SRC)" | tr " " "\n" | grep -n "$<" | cut -d : -f 1) \
		$(NUM_FILES) \
		$(shell echo $< | sed 's|$(SRC_DIR)/||g')
	@$(CC) $(CFLAGS) -I $(INC_DIR) -c $< -o $@

$(NAME): $(OBJ)
	@printf "\r$(CLEAR)%-15s: $(BRIGHT_GREEN)compilation finished$(END)\n" $(LIBRARY)
	@$(AR) $(ARFLAGS) $(NAME) $(OBJ)
	@printf "%-15s: create $(NAME)\n" $(LIBRARY)

# 必須ルール
.PHONY: all clean fclean re
all: $(NAME)

clean:
	@$(RM) -r $(OBJ_DIR)
	@printf "%-15s: remove $(OBJ_DIR)\n" $(LIBRARY)

fclean: clean
	@$(RM) $(NAME)
	@printf "%-15s: remove $(NAME)\n" $(LIBRARY)

re: fclean all

# その他のルール
.PHONY: norm test
norm:
	@norminette $(SRC) $(INC)

test: $(NAME) $(TEST) $(TEST_UTILS)
	@printf "%-15s: start test\n" $(LIBRARY)
	@$(RM) result.log
	@for test in $(TEST); do \
		$(CC) $(CFLAGS) -I $(INC_DIR) -I $(SRC_DIR) "$$test" $(TEST_UTILS) $(NAME) -o "$${test%.c}_"; \
		test_name=$$(echo "$$test" | sed "s|$(TEST_DIR)/||"); \
		printf "%-15s: $(BRIGHT_CYAN)%-30s$(END) ... " $(LIBRARY) "$$test_name"; \
		if valgrind --leak-check=full -q ./$${test%.c}_ 1>>result.log 2>&1; then \
			echo "$(BRIGHT_GREEN)OK$(END)"; \
		else \
			echo "$(BRIGHT_RED)KO (status: $$?)$(END)"; \
		fi; \
		$(RM) $${test%.c}_; \
	done;
	@printf "%-15s: end test\n" $(LIBRARY)
