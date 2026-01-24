
#include "minishell.h"

static int	open_redir_file(t_redir *redir)
{
	if (redir->type == REDIR_IN)
		return (open(redir->file, O_RDONLY));
	if (redir->type == REDIR_OUT)
		return (open(redir->file, O_WRONLY | O_CREAT | O_TRUNC, 0644));
	if (redir->type == APPEND)
		return (open(redir->file, O_WRONLY | O_CREAT | O_APPEND, 0644));
	if (redir->type == HEREDOC)
		return (handle_heredoc(redir->file));
	return (-1);
}

void	apply_saved_fds(t_cmd *cmd)
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
}

int	apply_one_redir(t_redir *r)
{
	int	fd;

	if (r->type == HEREDOC)
		return (0);
	fd = open_redir_file(r);
	if (fd < 0)
		return (-1);
	if (r->type == REDIR_IN)
		dup2(fd, STDIN_FILENO);
	else
		dup2(fd, STDOUT_FILENO);
	close(fd);
	return (0);
}

int	apply_redirections(t_cmd *cmd)
{
	t_redir	*redir;

	if (!cmd)
		return (0);
	apply_saved_fds(cmd);
	if (cmd->redirs)
	{
		redir = cmd->redirs;
		while (redir)
		{
			if (apply_one_redir(redir) < 0)
				return (-1);
			redir = redir->next;
		}
	}
	return (0);
}
