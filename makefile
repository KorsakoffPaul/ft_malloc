ifeq ($(HOSTTYPE),)
HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

NAME	= libft_malloc_$(HOSTTYPE).so
SYMLINK	= libft_malloc.so

CC		= cc
CFLAGS	= -Wall -Wextra -Werror -g -fPIC
LDFLAGS	= -shared

SRCDIR	= src
INCDIR	= includes
OBJDIR	= obj

SRCS	= malloc.c free.c show_alloc_memory.c realloc.c
OBJS	= $(SRCS:%.c=$(OBJDIR)/%.o)

LIBFT_DIR	= libft
LIBFT		= $(LIBFT_DIR)/libft.a

all : libft $(NAME) symlink

libft :
	$(NAME) -C $(LIBFT_DIR)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

$(OBJDIR)/%.o : $(SRCDIR)/%.c
	mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) -I$(INCDIR) -I$(LIBFT_DIR) -c $< -o $@

$(NAME) : $(OBJS) $(LIBFT)
	$(CC) $(LDFLAGS) $(OBJS) $(LIBFT) -o $(NAME)

symlink :
	ln -sf $(NAME) $(SYMLINK)

clean:
	rm -rf $(OBJDIR)
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME) $(SYMLINK)
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

# =======================
# Règle test
# ======================= utiliserexport LD_PRELOAD=/chemin/vers/libft_malloc.so pour se passer de preload pendant une session bash
TEST_SRC = test.c
TEST_BIN = test_malloc

test: all $(TEST_BIN)
	@echo "=== Test LD_PRELOAD ==="
	@LD_PRELOAD=./$(SYMLINK) ./$(TEST_BIN)

# Compilation du fichier test.c
$(TEST_BIN): $(TEST_SRC)
	$(CC) $(CFLAGS) $(TEST_SRC) -o $(TEST_BIN)