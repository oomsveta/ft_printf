NAME = libft.a

CC := cc
CFLAGS := -Wall -Wextra -Werror -Wmissing-prototypes -fPIC
CPPFLAGS := -MMD -MP -I.

UNAME_S := $(shell uname -s)
BUILD_STATE := .build_state
CURRENT_BUILD_STATE := "OS=$(UNAME_S) DEBUG=$(DEBUG) ASAN=$(ASAN)"

ifdef DEBUG
    CC := clang
    CFLAGS += -g3 -Og -fsanitize=undefined
else
    CFLAGS += -g -O3 -fno-builtin
endif

ifdef ASAN
	CFLAGS += -fsanitize=address
endif

SRC_DIR := src
SRC := $(addprefix $(SRC_DIR)/, \
			$(addprefix ctype/, ft_digittoint.c ft_isalnum.c ft_isalpha.c ft_isascii.c ft_isblank.c ft_iscntrl.c ft_isdigit.c ft_isgraph.c ft_islower.c ft_isprint.c ft_isupper.c ft_isxdigit.c ft_toupper.c ft_tolower.c) \
			$(addprefix string/, ft_bzero.c ft_memchr.c ft_memcmp.c ft_memcpy.c ft_memmove.c ft_memset.c ft_stpcpy.c ft_stpncpy.c ft_strchr.c ft_strchrnul.c ft_strcpy.c ft_strdup.c ft_strlcat.c ft_strlcpy.c ft_strlen.c ft_strlwr.c ft_strncmp.c ft_strnlen.c ft_strnstr.c ft_strrchr.c ft_strspn.c ft_strupr.c) \
			$(addprefix stdlib/, ft_abs.c ft_calloc.c ft_malloc.c ft_zmin.c) \
		)
OBJ := $(SRC:.c=.o)
DEP := $(OBJ:.o=.d)

AR ?= ar

all: $(NAME)

$(BUILD_STATE): FORCE
	@echo $(CURRENT_BUILD_STATE) > $@.tmp
	@cmp -s $@ $@.tmp || mv $@.tmp $@
	@$(RM) $@.tmp

$(NAME): $(OBJ)
	$(AR) rcs $@ $^

%.o: %.c $(BUILD_STATE)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

FORCE:

clean:
	$(RM) -- $(OBJ) $(DEP)

fclean: clean
	$(RM) -- $(NAME)

re: fclean all

norm:
	norminette $(SRC) *.h

compile_commands.json: fclean
	bear -- $(MAKE) all

-include $(DEP)

.PHONY: all clean fclean re norm
