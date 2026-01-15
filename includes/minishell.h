/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aletude- <aletude-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 15:07:16 by aletude-          #+#    #+#             */
/*   Updated: 2026/01/15 11:15:40 by aletude-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define _GNU_SOURCE

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <errno.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <dirent.h>
# include <signal.h>
# include <sys/wait.h>
# include <sys/time.h>
# include <sys/resource.h>
# include <sys/ioctl.h>
# include <termios.h>
# include <curses.h>
# include <term.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdbool.h>

# include "structs.h"
# include "../libft/libft.h"

// Retorno de função
# define SUCCESS 0
# define ERROR 1

// Boleanos
# define TRUE 1
# define FALSE 0

// FD padrão
# define STDIN 0
# define STDOUT 1
# define STDERR 2

// CMD saida bash
# define EXIT_CMD_NOT_FOUND 127 // Comando não encontrado
# define EXIT_CMD_NOT_EXEC 126 // Permissão negada
# define EXIT_SYNTAX_ERROR 2 // Erro de sintaxe
# define EXIT_SIGINT 130 // Interrompido por Ctrl+C

// Mensagens de Erro Padrão
# define ERR_PREFIX "minishell: "
# define ERR_SYNTAX "syntax error near unexpected token"
# define ERR_QUOTE "unexpected EOF while looking for matching quote"
// Cores
# define RED "\033[1;31m"
# define GREEN "\033[1;32m"
# define YELLOW "\033[1;33m"
# define BLUE "\033[1;34m"
# define RESET "\033[0m"

// variavel global
extern int	g_signal_status;

//create_cmd_util.c
t_cmd	*init_new_cmd(void);
void	add_arg_to_cmd(t_cmd *cmd, char *arg);
void	add_redir_to_cmd(t_cmd *cmd, t_token_type type, char *file_name);
void	cmd_add_back(t_cmd **lst, t_cmd *new);

//create_cmds.c
void	create_commands(t_mini *mini);

//token_list.c
t_token	*new_token(char *content, t_token_type type, t_quote quote);
void	token_add_back(t_token **lst, t_token *new);
void	free_tokens(t_token **tokens);

//lexer_utils.c
int		is_whitespace(char c);
int		is_operator(char *str);

//parser_manager.c
int		parse_input(t_mini *mini, char *input);

//lexer.c
int		tokenize_input(t_mini *mini, char *input);

//syntax.c
int		check_syntax(t_token *tokens);

// env_init.c
void	init_env(t_mini *mini, char **envp);

//env_utils.c
char	*get_env_value(t_env *env_list, char *key);

//expander_utils.c
int		get_var_len(char *str);
char	*get_token_value(t_mini *mini, char *var_name);

//expander.c
void	expand_variables(t_mini *mini);

//quote_remover.c
void	remove_quotes(t_mini *mini);

#endif