
#include "minishell.h"

static void	handle_in_redir(t_cmd *cmd, t_redir *r)
{
	if (cmd->fd_in != -1)
		close(cmd->fd_in);
	if (r->type == HEREDOC)
		cmd->fd_in = handle_heredoc(r->file);
	else if (r->type == REDIR_IN)
		cmd->fd_in = open(r->file, O_RDONLY);
}

static void	handle_out_redir(t_cmd *cmd, t_redir *r)
{
	int	flags;

	if (cmd->fd_out != -1)
		close(cmd->fd_out);
	if (r->type == REDIR_OUT)
		flags = O_CREAT | O_WRONLY | O_TRUNC;
	else
		flags = O_CREAT | O_WRONLY | O_APPEND;
	cmd->fd_out = open(r->file, flags, 0644);
}

void	handle_cmd_redirs(t_cmd *cmd)
{
	t_redir	*r;

	r = cmd->redirs;
	while (r)
	{
		if (r->type == HEREDOC || r->type == REDIR_IN)
			handle_in_redir(cmd, r);
		else if (r->type == REDIR_OUT || r->type == APPEND)
			handle_out_redir(cmd, r);
		r = r->next;
	}
}