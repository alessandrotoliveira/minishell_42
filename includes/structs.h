/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alessandro <alessandro@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 14:55:00 by aletude-          #+#    #+#             */
/*   Updated: 2026/01/13 20:47:47 by alessandro       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H
/*******ENUMS ********/
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

/******STRUCTS DE PARSING ********/
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

/* ========================================================================== */
/* STRUCTS DE EXECUÇÃO (Parser -> Executor)                                   */
/* ========================================================================== */

// NOVA STRUCT: Para lidar com múltiplos redirecionamentos (ls > a > b)
typedef struct s_redir
{
    t_token_type    type;      // REDIR_IN, REDIR_OUT, APPEND ou HEREDOC
    char            *file;     // Nome do arquivo ou Delimitador (se for heredoc)
    struct s_redir  *next;
}   t_redir;

typedef struct s_cmd
{
    char            **args;    // O comando e flags: {"ls", "-l", NULL}
    t_redir         *redirs;   // Lista de arquivos para redirecionar

    // Dados para o executor preencher (opcional no parser)
    int             pid;       // ID do processo (útil para o waitpid)
    struct s_cmd    *next;     // Próximo comando após o pipe
}   t_cmd;

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
