TEST_BIN := $(TEST_DIR)/tests.out
TEST_SRCS := $(TEST_DIR)/main.c $(wildcard $(TEST_DIR)/test_*.c)
TEST_BUILD_DIR := $(TEST_DIR)/build
TEST_OBJS := $(patsubst $(TEST_DIR)/%.c, $(TEST_BUILD_DIR)/%.o, $(TEST_SRCS))
TEST_DEPS := $(TEST_OBJS:.o=.d)

CMOCKA_DIR := $(TEST_DIR)/cmocka
CMOCKA_BUILD_DIR := $(CMOCKA_DIR)/build
CMOCKA_INCLUDE_DIR := $(CMOCKA_DIR)/include
CMOCKA_LIB = $(CMOCKA_BUILD_DIR)/src/libcmocka.a

TEST_INCLUDE := -I$(CMOCKA_INCLUDE_DIR)

$(CMOCKA_DIR)/CMakeLists.txt:
	git submodule update --init --recursive

$(CMOCKA_LIB): $(CMOCKA_DIR)/CMakeLists.txt
	cmake -S $(CMOCKA_DIR) -B $(CMOCKA_BUILD_DIR) -DCMAKE_BUILD_TYPE=Debug -DBUILD_SHARED_LIBS=OFF
	cmake --build $(CMOCKA_BUILD_DIR)

$(TEST_BUILD_DIR):
	@mkdir -p $@

$(TEST_OBJS): CPPFLAGS += $(TEST_INCLUDE)
$(TEST_OBJS): CFLAGS += -Wno-format
$(TEST_OBJS): $(TEST_BUILD_DIR)/%.o: $(TEST_DIR)/%.c $(BUILD_STATE) | $(TEST_BUILD_DIR)
	$(CC) $(CPPFLAGS) $(filter-out -Wmissing-prototypes, $(CFLAGS)) -c $< -o $@

$(TEST_BIN): $(OBJ) $(TEST_OBJS) $(CMOCKA_LIB) $(LIBFT)
	$(CC) $(CFLAGS) $(LDFLAGS) $^ -o $@

ifneq ($(filter test $(TEST_BIN),$(MAKECMDGOALS)),)
-include $(TEST_DEPS)
endif

test: $(TEST_BIN)
	./$<

clean-tests:
	$(RM) -r $(TEST_BUILD_DIR) $(TEST_BIN)

clean: clean-tests

.PHONY: clean-tests test
