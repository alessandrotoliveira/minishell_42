#ifndef MINISHELL_H
# define MINISHELL_H

/* ************************************************************************** */
/* INCLUDES                                  */
/* ************************************************************************** */

# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <dirent.h>
# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <errno.h>
# include <termios.h>
# include <unistd.h>

# include "struct.h"
# include "libft.h"

/* ************************************************************************** */
/* DEFINES                                  */
/* ************************************************************************** */

# define SUCCESS 0
# define ERROR   1

/* ************************************************************************** */
/* GLOBALS                                  */
/* ************************************************************************** */

extern volatile sig_atomic_t	g_received_signal;

/* ************************************************************************** */
/* PROTOTYPES                                 */
/* ************************************************************************** */

/* --- Parsing & Lexer --- */
int		parse_input(t_mini *mini, char *input);
int		tokenize_input(t_mini *mini, char *input);
int		check_syntax(t_token *tokens);
void	expand_variables(t_mini *mini);
void	remove_quotes(t_mini *mini);
char	*get_token_value(t_mini *mini, char *var_name);
int		get_var_len(char *str);

/* --- Token Utils --- */
t_token	*new_token(char *content, t_token_type type, t_quote quote);
void	token_add_back(t_token **lst, t_token *new);
void	free_tokens(t_token **tokens);
int		is_whitespace(char c);
int		is_operator(char *str);

/* --- Command Management --- */
void	create_commands(t_mini *mini);
t_cmd	*init_new_cmd(void);
void	add_arg_to_cmd(t_cmd *cmd, char *arg);
void	add_redir_to_cmd(t_cmd *cmd, t_token_type type, char *file_name);
void	cmd_add_back(t_cmd **lst, t_cmd *new);
void	free_commands(t_cmd *cmd);

/* --- Executor Core --- */
void	executor(t_mini *mini);
void	execute_pipeline(struct s_mini *mini);
void	child_process(t_cmd *cmd, t_mini *mini, char **paths, int is_pipeline);
void	wait_all_children(struct s_mini *mini, pid_t last_pid);
char	*find_cmd(char *cmd, char **paths);

/* --- Redirections & Heredoc --- */
int		apply_redirections(t_cmd *cmd);
int		handle_cmd_redirs(t_cmd *cmd);
void	handle_cmd_redirs_no_heredoc(t_cmd *cmd);
int		validate_redirs(t_cmd *cmd);
int		preprocess_heredocs(t_cmd *cmds);
int		handle_heredoc(char *delimiter);
int		create_heredoc_fd(char *delimiter);
int		write_heredoc_loop(int fd, char *delimiter);
char	*read_heredoc_line(void);

/* --- Builtins --- */
int		is_builtin(char *cmd_name);
void	execute_builtin(t_cmd *cmd, t_mini *mini);
int		builtin_echo(t_cmd *cmd);
int		builtin_pwd(t_cmd *cmd);
int		builtin_env(t_cmd *cmd, t_mini *mini);
int		builtin_cd(t_cmd *cmd, t_mini *mini);
int		builtin_exit(t_cmd *cmd, t_mini *mini);
int		builtin_export(t_cmd *cmd, t_mini *mini);
int		builtin_unset(t_cmd *cmd, t_mini *mini);
void	print_export_list(t_env *env);

/* --- Environment Utils --- */
void	init_env(t_mini *mini, char **envp);
char	*env_get(t_env *env, const char *key);
void	env_set(t_env **env_list, const char *key, const char *value);
char	**get_cmd_paths(t_env *env);
char	**convert_env_to_array(t_env *lstenv);
int		is_valid_identifier(char *str);
void	free_env_list(t_env *env);

/* --- Signals --- */
void	init_signals(void);
void	setup_heredoc_signal(struct sigaction *old);
void	restore_heredoc_signal(struct sigaction *old);

/* --- Memory, Errors & Unused --- */
void	free_matrix(char **matrix);
void	free_array(char **arr);
void	clean_and_exit(t_mini *mini, int exit_code);
// void	msg_error(char *msg);               // UNUSED
// void	cmd_error(char *cmd, char *msg);    // UNUSED
// void	free_cmd_list(t_cmd *cmd);          // UNUSED
// void	setup_pipeline_fds(t_cmd *cmd, int prev_fd); // UNUSED

#endif