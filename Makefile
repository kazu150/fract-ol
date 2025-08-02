# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kaisogai <kaisogai@student.42tokyo.jp>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/03 16:26:12 by kaisogai          #+#    #+#              #
#    Updated: 2025/08/02 12:26:02 by kaisogai         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= fractol
CC			= cc
CFLAGS		= -Wall -Wextra -Werror
SRC_DIR = src
OBJ_DIR = obj
TMP_DIR = tmp_objs
LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

SRCS = \
	$(SRC_DIR)/main.c $(SRC_DIR)/colors.c $(SRC_DIR)/complex.c \
	$(SRC_DIR)/validation.c $(SRC_DIR)/handlers.c  $(SRC_DIR)/draw.c

OBJS = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRCS))
MLX_DIR   = mlx
MLX       = $(MLX_DIR)/libmlx.a
MLX_FLAGS = -L$(MLX_DIR) -lmlx -lXext -lX11 -lm

LIBFT_OBJS = \
	ft_isalnum.o ft_isprint.o ft_memcpy.o ft_putendl_fd.o \
	ft_strchr.o ft_strlcat.o ft_strncmp.o ft_substr.o \
	ft_atoi.o ft_isalpha.o ft_itoa.o ft_memmove.o ft_putnbr_fd.o \
	ft_strdup.o ft_strlcpy.o ft_strnstr.o ft_tolower.o \
	ft_bzero.o ft_isascii.o ft_memchr.o ft_memset.o ft_putstr_fd.o \
	ft_striteri.o ft_strlen.o ft_strrchr.o ft_toupper.o \
	ft_calloc.o ft_isdigit.o ft_memcmp.o ft_putchar_fd.o ft_split.o \
	ft_strjoin.o ft_strmapi.o ft_strtrim.o \
	ft_printf.o ft_putnbr_base.o ft_putuint_fd.o \
	numlen.o print_nums.o print_words.o

all: $(LIBFT) $(MLX) $(NAME)

$(NAME): $(OBJS)
	@mkdir -p $(TMP_DIR)
	cp $(LIBFT) $(TMP_DIR)/
	cd $(TMP_DIR) && ar x libft.a
	$(CC) $(CFLAGS) $(OBJS) $(addprefix $(TMP_DIR)/, $(LIBFT_OBJS)) $(MLX_FLAGS) -o $(NAME)
	rm -rf $(TMP_DIR)

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR)

$(MLX):
	@$(MAKE) -C $(MLX_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR)
	@$(MAKE) -C $(LIBFT_DIR) clean
	@$(MAKE) -C $(MLX_DIR) clean

fclean: clean
	rm -f $(NAME)
	rm -f libft.a
	rm -f $(MLX)
	@$(MAKE) -C $(LIBFT_DIR) fclean
	@$(MAKE) -C $(MLX_DIR) clean

debug: CFLAGS += -g
debug: re

re: fclean all

.PHONY: all clean fclean re libft debug
