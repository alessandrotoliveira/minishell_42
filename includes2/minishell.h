#include <sys/types.h>
#include "struct.h"
#include "libft.h"
#include <readline/readline.h>
#include <readline/history.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <signal.h>
#include <signal.h>
#include <sys/wait.h>

void     execute_pipeline(struct s_mini *mini);
void     wait_all_children(struct s_mini *mini, pid_t last_pid);
int     is_builtin(char *cmd_name);
void	executor(t_mini *mini);
void	init_env(t_mini *mini, char **envp);
void	free_env_list(t_env *env);
void	free_commands(t_cmd *cmd);

char *env_get(t_env *env, const char *key);
void env_set(t_env **env_list, const char *key, const char *value);


/* Builtin prototypes */
int builtin_echo(t_cmd *cmd);
int builtin_pwd(t_cmd *cmd);
int builtin_env(t_cmd *cmd, t_mini *mini);
int builtin_cd(t_cmd *cmd, t_mini *mini);
int builtin_exit(t_cmd *cmd, t_mini *mini);
int builtin_export(t_cmd *cmd, t_mini *mini);
int builtin_unset(t_cmd *cmd, t_mini *mini);

/* Exec helpers */
char *find_cmd(char *cmd, char **paths);
char **get_cmd_paths(t_env *env);
char **convert_env_to_array(t_env *lstenv);

/* Additional prototypes */
void execute_builtin(t_cmd *cmd, t_mini *mini);
int apply_redirections(t_cmd *cmd);
void handle_cmd_redirs(t_cmd *cmd);
int handle_heredoc(char *delimiter);
void child_process(t_cmd *cmd, t_mini *mini, char **paths);
void free_array(char **arr);
void clean_and_exit(t_mini *mini, int exit_code);
int is_valid_identifier(char *str);
void print_export_list(t_env *env);