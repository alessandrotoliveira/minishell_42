# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aletude- <aletude-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/01/09 15:06:27 by aletude-          #+#    #+#              #
#    Updated: 2026/01/15 11:16:55 by aletude-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= minishell
CC			= cc
CFLAGS		= -Wall -Wextra -Werror -g3
INCLUDES	= -I includes -I libft

LIBFT_DIR	= libft
LIBFT		= $(LIBFT_DIR)/libft.a
LIBFT_FLAGS	= -L$(LIBFT_DIR) -lft -lreadline

SRC_DIR		=	src
OBJ_DIR		=	objs
SRC_FILES	= main.c \
			env/env_init.c \
			env/env_utils.c \
			parser/create_cmd_utils.c \
			parser/create_cmds.c \
			parser/expander_utils.c \
			parser/expander.c \
			parser/lexer_utils.c \
			parser/lexer.c \
			parser/parser_manager.c \
			parser/quote_remover.c \
			parser/syntax.c \
			parser/token_list.c \
			signals/signals.c \

SRCS		= $(addprefix $(SRC_DIR)/, $(SRC_FILES))
OBJS		= $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))

DEPS		= includes/minishell.h includes/structs.h

all: $(LIBFT) $(NAME)

$(LIBFT):
	@make -C $(LIBFT_DIR)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT_FLAGS) -o $(NAME)
	@echo "Minishell compiled successfully!"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(DEPS)
		@mkdir -p $(dir $@)
		$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
		@make clean -C $(LIBFT_DIR)
		rm -rf $(OBJ_DIR)

fclean: clean
		@make fclean -C $(LIBFT_DIR)
		rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
