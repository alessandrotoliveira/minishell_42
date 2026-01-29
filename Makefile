# --- Cores para estética ---
GREEN		= \033[0;32m
YELLOW		= \033[0;33m
BLUE		= \033[0;34m
MAGENTA		= \033[0;35m
CYAN		= \033[0;36m
RESET		= \033[0m

# --- Configurações de Compilação ---
NAME		= minishell
CC			= gcc
CFLAGS		= -Wall -Wextra -Werror -g
INCLUDES	= -I includes -I libft
RM			= rm -rf

# --- Caminhos ---
LIBFT_DIR	= libft
LIBFT		= $(LIBFT_DIR)/libft.a

# --- Fontes (Agrupados por módulo) ---
PARSER_SRCS	= src/parser/create_cmd_utils.c src/parser/create_cmds.c src/parser/expander_utils.c \
			  src/parser/expander.c src/parser/lexer_utils.c src/parser/lexer.c \
			  src/parser/parser_manager.c src/parser/quote_remover.c src/parser/syntax.c \
			  src/parser/token_list.c src/parser/word_split.c src/parser/word_split_utils.c

PIPELINE_SRCS = src/executor/pipeline/executor_main.c src/executor/pipeline/executor_utils.c \
			    src/executor/pipeline/exec_pipeline.c src/executor/pipeline/free_utils.c \
				src/executor/pipeline/path_utils.c src/executor/pipeline/exec_helpers.c

REDIR_SRCS	= src/executor/redirection/redirection.c src/executor/redirection/handle_redir.c \
			  src/executor/redirection/heredocs_utils.c src/executor/redirection/heredocs_files.c \
			  src/executor/redirection/heredocs_create.c src/executor/redirection/heredocs_process.c \
			  src/executor/redirection/heredocs_cleanup.c src/executor/redirection/redir_validation.c \
			  src/executor/redirection/heredocs_utils2.c

BUILTIN_SRCS = src/executor/builtins/builtin_cd.c src/executor/builtins/builtin_echo.c \
			  src/executor/builtins/builtin_env.c src/executor/builtins/builtin_exit.c \
			  src/executor/builtins/builtin_export.c src/executor/builtins/builtin_pwd.c \
			  src/executor/builtins/builtin_unset.c

ENV_SRCS	= src/executor/env/env_init.c src/executor/env/env_management.c src/executor/env/env_utils.c

SRCS		= src/main.c src/signals.c src/utils/cleanup.c \
			  $(PARSER_SRCS) $(PIPELINE_SRCS) $(REDIR_SRCS) $(BUILTIN_SRCS) $(ENV_SRCS)

OBJ_DIR		= objs
OBJS		= $(SRCS:%.c=$(OBJ_DIR)/%.o)

# --- Regras Principais ---
all: $(LIBFT) $(NAME)

$(NAME): $(OBJS)
	@echo "$(YELLOW)Compilando $(NAME)...$(RESET)"
	@$(CC) $(CFLAGS) $(INCLUDES) -o $(NAME) $(OBJS) $(LIBFT) -lreadline
	@echo "$(GREEN)✓ $(NAME) pronto!$(RESET)"

# Compilação dos objetos criando os subdiretórios necessários
$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	@printf "$(CYAN)Compilando:$(RESET) $(notdir $<)\n"
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(LIBFT):
	@echo "$(MAGENTA)Construindo Libft...$(RESET)"
	@$(MAKE) -C $(LIBFT_DIR) --no-print-directory

# --- Regras de Limpeza ---
clean:
	@$(RM) $(OBJ_DIR)
	@$(MAKE) -C $(LIBFT_DIR) clean --no-print-directory
	@echo "$(BLUE)Objetos removidos.$(RESET)"

fclean: clean
	@$(RM) $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean --no-print-directory
	@echo "$(BLUE)Binários removidos.$(RESET)"

re: fclean all

.PHONY: all clean fclean re