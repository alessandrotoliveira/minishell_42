#include "minishell.h"

static void	exec_external(t_cmd *cmd, t_mini *mini, char **paths)
{
	char	*path;
	char	**env_array;

	path = find_cmd(cmd->args[0], paths);
	env_array = convert_env_to_array(mini->env_list);
	if (!path)
	{
		ft_putstr_fd("minishell: command not found: ", 2);
		ft_putendl_fd(cmd->args[0], 2);
		free_array(paths);
		free_array(env_array);
		exit(127);
	}
	execve(path, cmd->args, env_array);
	perror("minishell: execve error");
	free(path);
	free_array(paths);
	free_array(env_array);
	if (errno == ENOENT)
		exit(127);
	else if (errno == EACCES || errno == EISDIR)
		exit(126);
	exit(1);
}

static void	setup_child_signals_and_redirs(t_cmd *cmd, int is_pipeline)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (!is_pipeline && isatty(STDIN_FILENO))
	{
		if (!handle_cmd_redirs(cmd))
			exit(1);
	}
	else
		handle_cmd_redirs_no_heredoc(cmd);
	if (apply_redirections(cmd) != 0)
		exit(1);
}

void	child_process(t_cmd *cmd, t_mini *mini, char **paths, int is_pipeline)
{
	setup_child_signals_and_redirs(cmd, is_pipeline);
	if (is_builtin(cmd->args[0]))
	{
		execute_builtin(cmd, mini);
		free_array(paths);
		exit(mini->exit_code);
	}
	exec_external(cmd, mini, paths);
}

void	executor(t_mini *mini)
{
	if (!mini->cmd_list || !mini->cmd_list->args)
		return ;
	if (mini->cmd_list->next && isatty(STDIN_FILENO) && !preprocess_heredocs(mini->cmd_list))
	{
		mini->exit_code = 130;
		return ;
	}
	if (!mini->cmd_list->next && is_builtin(mini->cmd_list->args[0]))
		execute_builtin(mini->cmd_list, mini);
	else
		execute_pipeline(mini);
}