/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnanque <bnanque@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 07:20:05 by aletude-          #+#    #+#             */
/*   Updated: 2026/01/27 15:59:00 by bnanque          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "struct.h"
# include "../libft/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <signal.h>
# include <errno.h>
# include <string.h>
# include <dirent.h>
# include <readline/readline.h>
# include <readline/history.h>

# define SUCCESS 1
# define ERROR 0

extern volatile sig_atomic_t	g_received_signal;

/* --- Signals --- */
void	init_signals(void);
void	setup_heredoc_signal(struct sigaction *old);
void	restore_heredoc_signal(struct sigaction *old);

/* --- Environment Management --- */
void	init_env(t_mini *mini, char **envp);
char	*env_get(t_env *env_list, const char *key);
void	env_set(t_env **env_list, const char *key, const char *value);
void	env_remove(t_env **env_list, char *key);
void	free_env_list(t_env *env_list);
char	**env_to_array(t_env *env_list);
char	**convert_env_to_array(t_env *env_list);

/* --- Parsing --- */
int		parse_input(t_mini *mini, char *input);
int		tokenize_input(t_mini *mini, char *input);
int		check_syntax(t_token *tokens);
void	expand_variables(t_mini *mini);
void	word_splitting(t_mini *mini);
void	remove_quotes(t_mini *mini);
t_token	*new_token(char *content, t_token_type type, t_quote quote);
void	add_token(t_token **tokens, t_token *new);
void	token_add_back(t_token **tokens, t_token *new);
void	free_tokens(t_token **tokens);
int		get_var_len(char *str);
char	*get_token_value(t_mini *mini, char *var_name);
int		is_whitespace(char c);
int		is_operator(char *str);

/* --- Command Management --- */
void	create_commands(t_mini *mini);
t_cmd	*init_new_cmd(void);
void	add_arg_to_cmd(t_cmd *cmd, char *arg);
void	add_redir_to_cmd(t_cmd *cmd, t_token_type type,
			char *file_name, t_quote quote);
void	cmd_add_back(t_cmd **lst, t_cmd *new);
void	free_commands(t_cmd *cmd);

/* --- Executor Core --- */
void	executor(t_mini *mini);
void	execute_pipeline(struct s_mini *mini);
void	child_process(t_cmd *cmd, t_mini *mini, char **paths, int is_pipeline);
void	wait_all_children(struct s_mini *mini, pid_t last_pid);
char	*find_cmd(char *cmd, char **paths);
char	**get_cmd_paths(t_env *env);
void	clean_and_exit(t_mini *mini, int exit_code);

/* --- Redirections & Heredoc --- */
int		apply_redirections(t_cmd *cmd);
void	apply_saved_fds(t_cmd *cmd);
int		handle_cmd_redirs(t_cmd *cmd);
void	handle_cmd_redirs_no_heredoc(t_cmd *cmd);
int		validate_redirs(t_cmd *cmd);
int		preprocess_heredocs(t_cmd *cmds, t_mini *mini);
int		handle_heredoc(char *delimiter);
int		create_heredoc_fd(char *delimiter, int expand, t_mini *mini);
int		write_heredoc_loop(int fd, char *delimiter, int expand, t_mini *mini);
char	*read_heredoc_line(void);
int		cleanup_on_interrupt(void);
int		check_output_dir_writable(char *file);
int		check_if_directory(char *path);
void	print_cmd_not_found(char *cmd);
void	try_exec_as_shell_script(char *path, t_cmd *cmd, char **env_array);
void	handle_execve_error(char *path, char **paths, char **env_array);
void	check_path_and_exit(char *path, char **paths, char **env_array);

/* --- Builtins --- */
int		is_builtin(char *cmd_name);
void	execute_builtin(t_cmd *cmd, t_mini *mini);
int		builtin_echo(t_cmd *cmd);
int		builtin_cd(t_cmd *cmd, t_mini *mini);
int		builtin_pwd(t_cmd *cmd);
int		builtin_export(t_cmd *cmd, t_mini *mini);
int		builtin_unset(t_cmd *cmd, t_mini *mini);
int		builtin_env(t_cmd *cmd, t_mini *mini);
int		builtin_exit(t_cmd *cmd, t_mini *mini);
int		is_valid_identifier(char *str);
void	print_export_list(t_env *env_list);

/* --- Utils --- */
void	free_array(char **arr);
char	*ft_getenv(t_env *env_list, char *var);
void	print_error(char *msg);

#endif
