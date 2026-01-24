#ifndef STRUCTS_H
# define STRUCTS_H

/* ************************************************************************** */
/*                                   ENUMS                                    */
/* ************************************************************************** */

typedef enum e_token_type
{
	WORD,
	PIPE,
	REDIR_IN,
	REDIR_OUT,
	HEREDOC,
	APPEND
}	t_token_type;

typedef enum e_quote
{
	NONE,
	SINGLE,
	DOUBLE
}	t_quote;

/* ************************************************************************** */
/*                                   PARSER                                   */
/* ************************************************************************** */

typedef struct s_token
{
	char			*content;
	t_token_type	type;
	t_quote			quote;
	struct s_token	*next;
	struct s_token	*prev;
}	t_token;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

/* ************************************************************************** */
/*                                  EXECUTOR                                  */
/* ************************************************************************** */

typedef struct s_redir
{
	t_token_type	type;
	char			*file;
	// int			hd_expand;   // UNUSED - kept for future use
	// int			append;      // UNUSED - kept for future use
	struct s_redir	*next;
}	t_redir;

typedef struct s_cmd
{
	char			**args;
	t_redir			*redirs;
	// int			pid;         // UNUSED - kept for future use
	int				fd_in;
	int				fd_out;
	struct s_cmd	*next;
}	t_cmd;

/* ************************************************************************** */
/*                                   CORE                                     */
/* ************************************************************************** */

typedef struct s_mini
{
	t_env	*env_list;
	t_cmd	*cmd_list;
	t_token	*tokens;
	int		exit_code;
	// char	**envp;        // UNUSED - kept for future use
	char	*input_line;
}	t_mini;

#endif
