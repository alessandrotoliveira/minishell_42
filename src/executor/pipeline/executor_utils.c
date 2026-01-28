/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aletude- <aletude-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 09:14:58 by aletude-          #+#    #+#             */
/*   Updated: 2026/01/26 09:14:58 by aletude-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin(char *cmd)
{
	if (!cmd)
		return (0);
	if (ft_strcmp(cmd, "echo") == 0 || ft_strcmp(cmd, "cd") == 0
		|| ft_strcmp(cmd, "pwd") == 0 || ft_strcmp(cmd, "export") == 0
		|| ft_strcmp(cmd, "unset") == 0 || ft_strcmp(cmd, "env") == 0
		|| ft_strcmp(cmd, "exit") == 0)
		return (1);
	return (0);
}

static void	exec_builtin_choice(t_cmd *cmd, t_mini *mini)
{
	char	*name;

	name = cmd->args[0];
	if (ft_strcmp(name, "echo") == 0)
		mini->exit_code = builtin_echo(cmd);
	else if (ft_strcmp(name, "pwd") == 0)
		mini->exit_code = builtin_pwd(cmd);
	else if (ft_strcmp(name, "env") == 0)
		mini->exit_code = builtin_env(cmd, mini);
	else if (ft_strcmp(name, "cd") == 0)
		mini->exit_code = builtin_cd(cmd, mini);
	else if (ft_strcmp(name, "export") == 0)
		mini->exit_code = builtin_export(cmd, mini);
	else if (ft_strcmp(name, "unset") == 0)
		mini->exit_code = builtin_unset(cmd, mini);
	else if (ft_strcmp(name, "exit") == 0)
		mini->exit_code = builtin_exit(cmd, mini);
}

void	execute_builtin(t_cmd *cmd, t_mini *mini)
{
	int		saved_fds[2];

	saved_fds[0] = dup(STDIN_FILENO);
	saved_fds[1] = dup(STDOUT_FILENO);
	if (apply_redirections(cmd) == 0)
		exec_builtin_choice(cmd, mini);
	else
		mini->exit_code = 1;
	dup2(saved_fds[0], STDIN_FILENO);
	dup2(saved_fds[1], STDOUT_FILENO);
	close(saved_fds[0]);
	close(saved_fds[1]);
}
