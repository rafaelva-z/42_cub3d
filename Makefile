# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fda-estr <fda-estr@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/07 16:21:22 by rvaz              #+#    #+#              #
#    Updated: 2024/01/21 23:04:48 by fda-estr         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.SILENT:
NAME		=	cub3d

CC			=	cc
CFLAGS		=	-Wall -Wextra -Werror -g #-fsanitize=address 
RM			=	/bin/rm -f

LIBFLAGS	=	-L$(LIBFT_PATH) -L$(MLX_PATH) -lft -lmlx -lXext -lX11 -lm -lz
INCLUDES	=	./include
LIBFT_PATH	=	./lib/libft/
LIBFT		=	$(LIBFT_PATH)libft.a
MLX_PATH	=	./lib/minilibx-linux/
MLX			=	$(MLX_PATH)libmlx.a

SRCS		=	$(addprefix ./src/,				\
				main.c							\
				parser.c						\
				parser_2.c						\
				utils.c							\
				)

OBJS = $(SRCS:.c=.o)

CYAN		=	\033[96m
RESET		=	\033[0m
TAG			=	$(CYAN)[$(NAME)]$(RESET)

%.o: %.c
	@$(CC) $(CFLAGS) -I$(INCLUDES) -c $< -o $@

all: $(NAME)

$(NAME): $(LIBFT) $(MLX) $(OBJS)
	@echo "$(TAG) Making Program"
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFLAGS) -o $(NAME)

$(LIBFT):
	@make -C $(LIBFT_PATH)

$(MLX):
	@make -C $(MLX_PATH)

clean:
	@$(RM) $(OBJS)
	@$(RM) $(OBJ_FOLDER)
	@make -C $(LIBFT_PATH) clean
	@make -C $(MLX_PATH) clean

fclean: clean
	@echo "$(TAG) Full clean." 
	@make -C $(LIBFT_PATH) fclean
	@$(RM) $(NAME)

re: fclean all
	@echo "$(TAG) Recompiling."
	@make -C $(LIBFT_PATH) re

run: $(NAME)
	@clear
	./$(NAME)

runvg: $(NAME)
	@clear
	valgrind --leak-check=full --show-leak-kinds=all --track-fds=yes ./$(NAME)

.PHONY: all clean fclean re run runvg
