NAME := libftprintf.a

CC := cc
AR := ar

LIBFT_DIR := libft
LIBFT := $(LIBFT_DIR)/libft.a

ARFLAGS := rcs
LDFLAGS := -L$(LIBFT_DIR)
LDLIBS := -lft
CFLAGS := -Wall -Wextra -Werror -Wvla -Wmissing-prototypes
DEPFLAGS := -MMD -MP
CPPFLAGS := $(DEPFLAGS) -I$(LIBFT_DIR) -Iinclude

SRC_DIR := src
BUILD_DIR := build

SRC := $(addprefix $(SRC_DIR)/, parser.c)
OBJ := $(SRC:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)
DEP := $(OBJ:.o=.d)

UNAME_S := $(shell uname -s)
BUILD_STATE := $(BUILD_DIR)/.build_state
CURRENT_BUILD_STATE := "OS=$(UNAME_S) DEBUG=$(DEBUG) ASAN=$(ASAN)"

ifdef DEBUG
    CC := clang
    CFLAGS += -g3 -Og -fsanitize=undefined
else
    CFLAGS += -O3 -g0 -fno-builtin
endif

ifdef ASAN
	CFLAGS += -fsanitize=address
endif

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT)
	cp -- $(LIBFT) $@
	$(AR) $(ARFLAGS) $@ $(OBJ)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c $(BUILD_STATE) | $(BUILD_DIR)
	@mkdir -p $(@D)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

$(LIBFT): FORCE
	@$(MAKE) -C $(LIBFT_DIR)

$(BUILD_STATE): FORCE | $(BUILD_DIR)
	@echo $(CURRENT_BUILD_STATE) > $@.tmp
	@cmp -s $@ $@.tmp || mv $@.tmp $@
	@$(RM) $@.tmp

$(BUILD_DIR):
	mkdir -p $@

FORCE:

asan:
	@$(MAKE) DEBUG=1 ASAN=1 re

debug:
	@$(MAKE) DEBUG=1 re

clean:
	$(RM) -r -- $(BUILD_DIR)
	@$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	$(RM) -- $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

compile_commands.json: fclean
	bear -- $(MAKE) all

ifeq (,$(filter asan clean debug fclean re, $(MAKECMDGOALS)))
-include $(DEP)
endif

.PHONY: asan clean debug fclean re

TEST_DIR := tests
-include $(TEST_DIR)/tests.mk
