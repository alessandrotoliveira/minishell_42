/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_main.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnanque <bnanque@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 09:14:43 by aletude-          #+#    #+#             */
/*   Updated: 2026/01/27 15:51:36 by bnanque          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	exec_external(t_cmd *cmd, t_mini *mini, char **paths)
{
	char	*path;
	char	**env_array;

	path = find_cmd(cmd->args[0], paths);
	env_array = convert_env_to_array(mini->env_list);
	if (!path)
	{
		print_cmd_not_found(cmd->args[0]);
		free_array(paths);
		free_array(env_array);
		exit(127);
	}
	check_path_and_exit(path, paths, env_array);
	execve(path, cmd->args, env_array);
	if (errno == ENOEXEC)
		try_exec_as_shell_script(path, cmd, env_array);
	handle_execve_error(path, paths, env_array);
}

static void	setup_child_signals_and_redirs(t_cmd *cmd, int is_pipeline)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (is_pipeline)
	{
		if (apply_redirections(cmd) != 0)
			exit(1);
	}
	else
	{
		apply_saved_fds(cmd);
		if (apply_redirections(cmd) != 0)
			exit(1);
	}
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

static int	validate_command(t_mini *mini)
{
	if (!mini->cmd_list || !mini->cmd_list->args)
		return (0);
	if (!mini->cmd_list->args[0] || !mini->cmd_list->args[0][0])
		return (0);
	return (1);
}

void	executor(t_mini *mini)
{
	if (!validate_command(mini))
		return ;
	if (!preprocess_heredocs(mini->cmd_list, mini))
	{
		mini->exit_code = 130;
		return ;
	}
	if (!mini->cmd_list->next && is_builtin(mini->cmd_list->args[0]))
		execute_builtin(mini->cmd_list, mini);
	else
		execute_pipeline(mini);
}
