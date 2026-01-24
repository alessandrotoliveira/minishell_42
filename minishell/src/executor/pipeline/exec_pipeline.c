
#include "minishell.h"

static void setup_child_fds(t_cmd *cmd, int prev_fd, int *pipefd)
{
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

static int	pre_check_cmds(t_cmd *cmd, int *exit_code)
{
	while (cmd)
	{
		if (!validate_redirs(cmd))
		{
			perror("minishell");
			*exit_code = 1;
			return (0);
		}
		cmd = cmd->next;
	}
	return (1);
}

void	execute_pipeline(t_mini *mini)
{
	t_cmd	*c;
	int		p_fd[2];
	int		prev_fd;
	pid_t	pid;
	char	**paths;

	if (!pre_check_cmds(mini->cmd_list, &mini->exit_code))
		return ;
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
			setup_child_fds(c, prev_fd, p_fd);
			child_process(c, mini, paths, (mini->cmd_list->next != NULL));
		}
		update_parent_fds(c, &prev_fd, p_fd);
		c = c->next;
	}
	free_array(paths);
	wait_all_children(mini, pid);
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
				break;
			if (errno == EINTR)
				continue;
			break;
		}
		if (current_pid == last_pid)
		{
			if (WIFEXITED(status))
				mini->exit_code = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				mini->exit_code = 128 + WTERMSIG(status);
		}
	}
}