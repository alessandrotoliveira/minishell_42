
#include "minishell.h"

/*
** Conecta os pipes e os redirecionamentos de ficheiro no processo filho.
*/
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
    if (cmd->fd_in != -1)
    {
        dup2(cmd->fd_in, STDIN_FILENO);
        close(cmd->fd_in);
    }
    if (cmd->fd_out != -1)
    {
        dup2(cmd->fd_out, STDOUT_FILENO);
        close(cmd->fd_out);
    }
}

static void	parent_process_update(int *prev_fd, int *pipefd, t_cmd *c)
{
	if (*prev_fd != -1)
		close(*prev_fd);
	if (c->next)
	{
		close(pipefd[1]);
		*prev_fd = pipefd[0];
	}
	else
		*prev_fd = -1;
}

void	execute_pipeline(t_mini *mini)
{
	t_cmd	*c;
	int		pipefd[2];
	int		prev_fd;
	pid_t	pid;
	char	**paths;

	paths = get_cmd_paths(mini->env_list);
	c = mini->cmd_list;
	prev_fd = -1;
	while (c)
	{
		handle_cmd_redirs(c);
		if (c->next && pipe(pipefd) < 0)
			break ;

		pid = fork();
		if (pid == 0)
		{
			setup_child_fds(c, prev_fd, pipefd);
			child_process(c, mini, paths);
		}
		parent_process_update(&prev_fd, pipefd, c);
		
		if (c->fd_in != -1)
			close(c->fd_in);
		if (c->fd_out != -1)
			close(c->fd_out);
			
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
		if (current_pid <= 0)
			break ;
		if (current_pid == last_pid)
		{
			if (WIFEXITED(status))
				mini->exit_code = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				mini->exit_code = 128 + WTERMSIG(status);
		}
	}
}
