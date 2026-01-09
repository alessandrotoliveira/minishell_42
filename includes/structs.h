/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aletude- <aletude-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 14:55:00 by aletude-          #+#    #+#             */
/*   Updated: 2026/01/09 15:05:32 by aletude-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include <stdbool.h> 

// Enum para facilitar a leitura do tipo de token.
typedef enum e_token_type
{
	WORD,
	PIPE,
	REDIR_IN,
	REDIR_OUT,
	HEREDOC,
	APPEND,
}	t_token_type;

// Novo Enum para controlar aspas (Crucial para expansão de $) 
// SINGLE - Nao expande / DOUBLE - Expande apenas $
typedef enum e_quote
{
	NONE,
	SINGLE,
	DOUBLE,
}	t_quote;

//Estrutura para a lista de tokens (Lexer)
typedef struct s_token
{
	char			*content;
	t_token_type	type;
	t_quote			quote;
	struct s_token	*next;
	struct s_token	*prev;
}	t_token;
// Variavel de ambiente / key - nome / value - valor
typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;
// Estrutura Principal de Comando (Parser -> Executor)
typedef struct s_cmd
{
	char			**args;
	char			*cmd_path;
	int				fd_in;
	int				fd_out;
	char			*heredoc_delim;
	char			*infile_name;
	char			*outfile_name;
	struct s_cmd	*next;
}	t_cmd;

// Centraliza tudo para facilitar a limpeza e acesso.
typedef struct s_mini
{
	t_env	*env_list;
	t_cmd	*cmd_list;
	t_token	*tokens;
	int		exit_code;
	char	**envp;
}	t_mini;

#endif