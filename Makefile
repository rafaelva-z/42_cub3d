# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rvaz <rvaz@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/07 16:21:22 by rvaz              #+#    #+#              #
#    Updated: 2024/01/17 20:46:53 by rvaz             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.SILENT:
NAME		=	cub3d
CC			=	cc
CFLAGS		=	-Wall -Wextra -Werror -g #-fsanitize=address 
LIBFLAGS	=	-L$(LIBFT_PATH) -lft
RM			=	/bin/rm -f
INCLUDES	=	./include
LIBFT_PATH	=	./lib/libft/
LIBFT		=	$(LIBFT_PATH)libft.a
SRCS		=	$(addprefix ./src/,				\
				main.c							\
				)								\

OBJS = $(SRCS:.c=.o)

CYAN		=	\033[96m
RESET		=	\033[0m
TAG			=	$(CYAN)[$(NAME)]$(RESET)

%.o: %.c
	@$(CC) $(CFLAGS) -I$(INCLUDES) -c $< -o $@

all: $(NAME)

$(NAME): $(LIBFT) $(OBJS)
	@echo "$(TAG) Making Program"
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFLAGS) -o $(NAME)

$(LIBFT):
	@make -C $(LIBFT_PATH)

clean:
	@$(RM) $(OBJS)
	@make -C $(LIBFT_PATH) clean
	@$(RM) $(OBJ_FOLDER) readline.supp

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
