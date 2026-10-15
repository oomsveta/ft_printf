NAME := tests.out

CC := clang

FT_PRINTF_DIR := ..
FT_PRINTF_INCLUDE_DIR := $(FT_PRINTF_DIR)/include
FT_PRINTF_LIB := $(FT_PRINTF_DIR)/libftprintf.a

CMOCKA_DIR := cmocka
CMOCKA_BUILD_DIR := $(CMOCKA_DIR)/build
CMOCKA_INCLUDE_DIR := $(CMOCKA_DIR)/include
CMOCKA_LIB = $(CMOCKA_BUILD_DIR)/src/libcmocka.a

TEST_SRCS := $(wildcard test_*.c)
TEST_BUILD_DIR := build
TEST_OBJS := $(TEST_SRCS:%.c=$(TEST_BUILD_DIR)/%.o)
TEST_DEPS := $(TEST_OBJS:.o=.d)

CFLAGS := -Wall -Wextra -Og -g3 -fsanitize=undefined
DEPFLAGS := -MMD -MP
CPPFLAGS := $(DEPFLAGS) -I$(FT_PRINTF_INCLUDE_DIR) -I$(CMOCKA_INCLUDE_DIR)

ifdef ASAN
	CFLAGS += -fsanitize=address
endif

all: $(NAME)

$(NAME): $(TEST_OBJS) $(CMOCKA_LIB) $(FT_PRINTF_LIB)
	$(CC) $(CFLAGS) $^ -o $@

$(TEST_BUILD_DIR):
	mkdir -p $@

$(TEST_OBJS): $(TEST_BUILD_DIR)/%.o: %.c | $(TEST_BUILD_DIR)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

$(FT_PRINTF_LIB): FORCE
	$(MAKE) DEBUG=1 -C $(FT_PRINTF_DIR)

$(CMOCKA_DIR)/CMakeLists.txt:
	git submodule update --init --recursive

$(CMOCKA_LIB):
	cmake -S $(CMOCKA_DIR) -B $(CMOCKA_BUILD_DIR) -DCMAKE_BUILD_TYPE=Debug -DBUILD_SHARED_LIBS=OFF
	cmake --build $(CMOCKA_BUILD_DIR)

compile_commands.json: fclean
	bear -- $(MAKE) all

FORCE:

asan:
	$(MAKE) ASAN=1 re

clean:
	$(RM) -r -- $(TEST_BUILD_DIR)

fclean: clean
	$(RM) -- $(NAME)

re: fclean all

.PHONY: all asan clean fclean re
