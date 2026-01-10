ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

NAME	= libft_malloc_$(HOSTTYPE).so
SYMLINK	= libft_malloc.so

CC		= cc
CFLAGS	= -g -fPIC #-Wall -Wextra -Werror 
LDFLAGS	= -shared

SRCDIR	= src
INCDIR	= includes
OBJDIR	= obj

SRCS	= malloc.c free.c show_alloc_memory.c realloc.c
OBJS	= $(SRCS:%.c=$(OBJDIR)/%.o)

LIBFT_DIR	= libft
LIBFT		= $(LIBFT_DIR)/libft.a

all : libft $(NAME) $(SYMLINK)

libft :
	$(NAME) -C $(LIBFT_DIR)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

$(OBJDIR)/%.o : $(SRCDIR)/%.c
	mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) -I$(INCDIR) -I$(LIBFT_DIR) -c $< -o $@

$(NAME) : $(OBJS) $(LIBFT)
	$(CC) $(LDFLAGS) $(OBJS) $(LIBFT) -o $(NAME)

$(SYMLINK): $(NAME)
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
# ======================= 
TEST_SRC = test.c
TEST_BIN = test_malloc

test: all $(TEST_BIN)
	@echo "=== Test ==="
	@LD_LIBRARY_PATH=. LD_PRELOAD=./$(SYMLINK) ./$(TEST_BIN)
#library path permet d'ajouter le repertoire courant pour detecter malloc.so
#preload permet de charger mon malloc avant celui du pc

# Compilation du fichier test.c
$(TEST_BIN): $(TEST_SRC)
	$(CC) $(CFLAGS) $(TEST_SRC) \
		-L. -Wl,--no-as-needed -lft_malloc \
		-o $(TEST_BIN)
#no as needed force le compilateur a garder show alloc mem
#lft_malloc aussi necessaire pour SAM
#-L permet au linker de trouver la biblio


#sinon executer comme ca LD_LIBRARY_PATH=. LD_PRELOAD=./libft_malloc.so ./test_malloc
#après avoir compilé comme ca cc test.c -L. -Wl,--no-as-needed -lft_malloc -o test_malloc