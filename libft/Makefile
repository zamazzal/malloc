# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: zamazzal <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/10/06 19:38:09 by zamazzal          #+#    #+#              #
#    Updated: 2020/12/12 20:36:14 by zamazzal         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
H = libft.h
FLAGS = -Wall -Wextra -Werror

SRC_PATH = sources/
OBJ_PATH = objects/
INC_PATH = includes/

SRC =	ft_atoi.c       ft_bzero.c      ft_goodstr.c    ft_isspace.c    ft_itoa.c       \
		ft_isalnum.c    ft_isalpha.c    ft_isascii.c    ft_isdigit.c    ft_isprint.c    \
		ft_lstadd.c     ft_lstdel.c     ft_lstdelone.c  ft_lstiter.c    ft_lstlen.c     \
		ft_lstmap.c     ft_lstnew.c     ft_memalloc.c   ft_memccpy.c    ft_memchr.c     \
		ft_memmove.c    ft_memset.c     ft_memdel.c     ft_memcpy.c     ft_memcmp.c     \
		ft_putnbr.c     ft_putnbr_fd.c  ft_putendl_fd.c ft_putendl.c    ft_nbrlen.c     \
		ft_strdup.c		ft_strequ.c		ft_strdel.c		ft_strcpy.c		ft_strcmp.c		\
		ft_strcat.c		ft_strchr.c		ft_puttables.c  ft_putstr_fd.c  ft_putstr.c		\
		ft_strncpy.c	ft_strndup.c	ft_strncmp.c    ft_strmap.c		ft_putchar_fd.c \
		ft_strnequ.c    ft_strnew.c		ft_strncat.c    ft_strlwr.c		ft_putchar.c	\
		ft_strnstr.c    ft_strrchr.c    ft_strmapi.c    ft_strlen.c		ft_strsplit.c	\
		ft_striteri.c   ft_strjoin.c    ft_striter.c    ft_strclr.c		ft_strstr.c		\
		ft_tolower.c    ft_toupper.c    ft_strupper.c   ft_strlcat.c	ft_strsub.c		\
		ft_strtrim.c

SRCS = $(addprefix $(SRC_PATH), $(SRC))
OBJS = $(addprefix $(OBJ_PATH), $(SRC:.c=.o))
HEAD = $(addprefix $(INC_PATH), $(H))

all : $(NAME)

$(NAME) : $(OBJS)
	@ar rc $(NAME) $(OBJS)
	@ranlib $(NAME)
	@echo "\x1B[96mLibft : \x1B[90;0m[\x1B[34;1m $(NAME) \x1B[90;0m] \x1B[32mCreated.\x1B[39;0m"

$(OBJ_PATH)%.o: $(SRC_PATH)%.c $(HEAD)
	@mkdir -p $(OBJ_PATH)
	@gcc $(FLAGS) -I $(INC_PATH) -c $< -o $@

clean :
	@rm -rf $(OBJ_PATH)
	@echo "\x1B[96mLibft : \x1B[90;0m[\x1B[34;1m Objects \x1B[90;0m] \x1B[31mDeleted.\x1B[39;0m"

fclean : clean
	@rm -f $(NAME)
	@echo "\x1B[96mLibft : \x1B[90;0m[\x1B[34;1m $(NAME) \x1B[90;0m] \x1B[31mDeleted.\x1B[39;0m"

re : fclean all

.PHONY: all, clean, fclean, re
