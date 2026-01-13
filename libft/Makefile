# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pkorsako <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/12/20 21:27:10 by pkorsako          #+#    #+#              #
#    Updated: 2022/02/05 17:29:45 by pkorsako         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

SRCDIR      = src
INCDIR      = includes
OBJDIR      = obj

CC	= cc
CFLAGS	= -Wall -fPIC -Werror -Wextra -I$(INCDIR)
#HEADER = libft.h

SRC =	ft_isalpha.c	\
		ft_isalnum.c	\
		ft_isdigit.c	\
		ft_isascii.c	\
		ft_isprint.c	\
		ft_tolower.c	\
		ft_toupper.c	\
		ft_memset.c		\
		ft_memcpy.c		\
		ft_memchr.c		\
		ft_memcmp.c		\
		ft_memmove.c	\
		ft_strlen.c		\
		ft_bzero.c		\
		ft_atoi.c		\
		ft_strdup.c		\
		ft_strchr.c		\
		ft_striteri.c	\
		ft_strrchr.c	\
		ft_strlcat.c	\
		ft_strlcpy.c	\
		ft_strncmp.c	\
		ft_strnstr.c	\
		ft_calloc.c		\
		ft_substr.c		\
		ft_strjoin.c	\
		ft_strtrim.c	\
		ft_itoa.c		\
		ft_putchar_fd.c	\
		ft_putstr_fd.c	\
		ft_putnbr_fd.c	\
		ft_split.c		\
		ft_strmapi.c	\
		ft_putendl_fd.c	\
		ft_printf.c

OBJ	= $(SRC:%.c=$(OBJDIR)/%.o)
#OBJ =	$(SRC:.c=.o)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@
#%.o	: %.c $(HEADER)
#	$(CC) -c $(CFLAGS) $< -o $@

all	: $(NAME)

$(NAME)	: $(OBJ)
	ar rc $(NAME) $(OBJ)

clean	:
	rm -rf $(OBJDIR)

fclean	: clean
	rm -f $(NAME)

re	: fclean all
