/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipeline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 09:11:26 by aletude-          #+#    #+#             */
/*   Updated: 2026/01/29 00:51:54 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	setup_child_fds_and_redirs(t_cmd *cmd, int prev_fd, int *pipefd)
{
	if (cmd->fd_in != -1)
	{
		dup2(cmd->fd_in, STDIN_FILENO);
		close(cmd->fd_in);
		cmd->fd_in = -1;
	}
	if (cmd->fd_out != -1)
	{
		dup2(cmd->fd_out, STDOUT_FILENO);
		close(cmd->fd_out);
		cmd->fd_out = -1;
	}
	if (prev_fd != -1)
	{
		dup2(prev_fd, STDIN_FILENO);
		close(prev_fd);
	}
	if (cmd->next)
	{
		close(pipefd[0]);
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[1]);
	}
}

static void	update_parent_fds(t_cmd *c, int *prev_fd, int *pipefd)
{
	if (c->next)
	{
		close(pipefd[1]);
		if (*prev_fd != -1)
			close(*prev_fd);
		*prev_fd = pipefd[0];
	}
	else if (*prev_fd != -1)
	{
		close(*prev_fd);
		*prev_fd = -1;
	}
	if (c->fd_in != -1)
		close(c->fd_in);
	if (c->fd_out != -1)
		close(c->fd_out);
}


void	execute_pipeline(t_mini *mini)
{
	t_cmd	*c;
	int		p_fd[2];
	int		prev_fd;
	pid_t	pid;
	char	**paths;

	paths = get_cmd_paths(mini->env_list);
	c = mini->cmd_list;
	prev_fd = -1;
	while (c)
	{
		if (c->next && pipe(p_fd) < 0)
			break ;
		pid = fork();
		if (pid == 0)
		{
			setup_child_fds_and_redirs(c, prev_fd, p_fd);
			child_process(c, mini, paths, (mini->cmd_list->next != NULL));
		}
		update_parent_fds(c, &prev_fd, p_fd);
		c = c->next;
	}
	free_array(paths);
	wait_all_children(mini, pid);
}

static void	process_child_status(t_mini *mini, int status)
{
	int	sig;

	if (WIFEXITED(status))
		mini->exit_code = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
	{
		sig = WTERMSIG(status);
		mini->exit_code = 128 + sig;
	}
}

void	wait_all_children(t_mini *mini, pid_t last_pid)
{
	int		status;
	pid_t	current_pid;

	while (1)
	{
		current_pid = wait(&status);
		if (current_pid < 0)
		{
			if (errno == ECHILD)
				break ;
			if (errno == EINTR)
				continue ;
			break ;
		}
		if (WIFSIGNALED(status) && WTERMSIG(status) == SIGQUIT)
			ft_putstr_fd("Quit (core dumped)\n", STDERR_FILENO);
		if (current_pid == last_pid)
			process_child_status(mini, status);
	}
}
