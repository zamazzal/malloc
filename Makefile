# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: zamazzal <zouhir.amazzal@gmail.com>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/12/22 16:08:23 by zamazzal          #+#    #+#              #
#    Updated: 2020/12/22 17:22:40 by zamazzal         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

##### vars
DEBUG = 0
LOG = 0

ifeq ($(HOSTTYPE),)
		HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

NAME = libft_malloc.so
TARGET = libft_malloc_$(HOSTTYPE).so

SRCS_PATH = sources/
OBJS_PATH = objects/
LIBFT_PATH = libft/
HEADER_PATH = includes/
LIBFT_HEADER_PATH = $(addprefix $(LIBFT_PATH), $(HEADER_PATH))

MALLOC_HEADER = malloc.h
LIBFT_HEADER = libft.h

LIBFT_NAME = libft.a
LIBFT_LIBRARY = $(addprefix $(LIBFT_PATH), $(LIBFT_NAME))

HEADERS = 	$(addprefix $(LIBFT_HEADER_PATH), $(LIBFT_HEADER)) \
			$(addprefix $(HEADER_PATH), $(MALLOC_HEADER))

SRCS =	create_block.c \
		create_zone.c \
		free_logs.c \
		ft_blocks_info.c \
		ft_free.c \
		ft_malloc.c \
		ft_realloc.c \
		lists_management.c \
		malloc_logs.c \
		show_mem.c \
		show_mem_ex.c \
		tools.c

OBJS = ${SRCS:.c=.o}

SRCS_FILES = $(addprefix $(SRCS_PATH), $(SRCS))
OBJ_FILES = $(addprefix $(OBJS_PATH), $(OBJS))

GCC = gcc
FLAGS = -Wall -Wextra -Werror
SHARED_FLAGS = -shared
OBJ_FLAGS = -c -FPIC
LIB_FT =	-L $(LIBFT_PATH) -lft
HEADERS_LINK = -I $(LIBFT_HEADER_PATH) -I $(HEADER_PATH)

VARS = -D DEBUG=$(DEBUG) -D LOG=$(LOG)

all : $(NAME)

$(NAME) : $(TARGET)
	@ln -s $(TARGET) $(NAME)
	@echo "\x1B[96mLibrary Link \x1B[90;0m[\x1B[34;1m $(NAME) \x1B[90;0m] \x1B[32mCreated.\x1B[39;0m"

$(TARGET) : $(OBJ_FILES) $(HEADERS) $(LIBFT_LIBRARY)
	@$(GCC) $(VARS)  $(SHARED_FLAGS) $(OBJ_FILES) $(HEADERS_LINK) $(LIB_FT) -o $(TARGET)
	@echo "\x1B[96mShared Library \x1B[90;0m[\x1B[34;1m $(TARGET) \x1B[90;0m] \x1B[32mCreated.\x1B[39;0m"

$(OBJS_PATH)%.o : $(SRCS_PATH)%.c $(HEADERS)
	@mkdir -p $(OBJS_PATH)
	@$(GCC) $(VARS) $(OBJ_FLAGS) $(FLAGS) $(HEADERS_LINK) $< -o $@
	@echo "\x1B[96mObject File \x1B[90;0m[\x1B[34;1m $(notdir $@) \x1B[90;0m] \x1B[32mCreated.\x1B[39;0m"

$(LIBFT_LIBRARY) : $(LIBFT_PATH)
	@make -C $(LIBFT_PATH)

clean:
	@rm -rf $(OBJS_PATH)
	@echo "\x1B[96mObjects Files \x1B[31mDeleted.\x1B[39;0m"
	@make -C $(LIBFT_PATH) clean

fclean:
	@rm -rf $(OBJS_PATH)
	@echo "\x1B[96mObjects Files \x1B[31mDeleted.\x1B[39;0m"
	@rm -rf $(NAME) $(TARGET)
	@make -C $(LIBFT_PATH) fclean
	@echo "\x1B[96mShared Library \x1B[90;0m[\x1B[34;1m $(TARGET) \x1B[90;0m] \x1B[31mDeleted.\x1B[39;0m"
	@echo "\x1B[96mLibrary Link \x1B[90;0m[\x1B[34;1m $(NAME) \x1B[90;0m] \x1B[31mDeleted.\x1B[39;0m"

re: fclean all

.PHONY: all, clean, fclean, re
