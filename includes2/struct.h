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
// type: REDIR_IN, REDIR_OUT, APPEND ou HEREDOC
// file: Nome do arquivo ou delimitador (se for heredoc)
typedef struct s_redir
{
	t_token_type	type;
	char			*file;
	int 			hd_expand; // estes campos guardam configurações especificas que o lexer
	int             append;//precisa mas o executor precisa aplicar.
	struct s_redir	*next;
}	t_redir;

//args: O comando e flags: {"ls", "-l", NULL}
// redirs: Lista de arquivos para redirecionar
// Dados para o executor preencher (opcional no parser)
// pid: ID do processo (útil para o waitpid)
//*next: Proximo comando após pipe
typedef struct s_cmd
{
	char			**args;
	t_redir			*redirs;
	int				pid; // serve para armazenar o ID do processo que o fork criou para comando.
	int             fd_in; // fd_in e fd_out adicionei esse dois campos para executor saber exatamente
	int			    fd_out;//para  onde redirecionar a entrada e saída antes de executar o comando.
	struct s_cmd	*next;
}	t_cmd;

// Centraliza tudo para facilitar a limpeza e acesso.
typedef struct s_mini
{
	t_env	*env_list;
	t_cmd	*cmd_list;
	t_token	*tokens;
	int		exit_code;
	char	**envp;//centraliza todas as variaveis de ambiente para facilitar a limpeza e acesso.
	char   *input_line;//centraliza a linha de entrada para facilitar a limpeza e acesso.
}	t_mini;

#endif
