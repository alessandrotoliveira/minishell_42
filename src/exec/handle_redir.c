
#include "minishell.h"
/*
** Abre o arquivo correto baseado no tipo de redirecionamento.
** Se houver erro (permissão, arquivo inexistente), retorna -1.
*/
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

int	apply_redirections(t_cmd *cmd)
{
	t_redir	*r;
	int		fd;

	if (cmd->fd_in != -1)
	{
		dup2(cmd->fd_in, STDIN_FILENO);
		close(cmd->fd_in);
	}
	r = cmd->redirs;
	while (r)
	{
		if (r->type == REDIR_IN || r->type == REDIR_OUT || r->type == APPEND)
		{
			fd = open_redir_file(r);
			if (fd < 0)
				return (perror(r->file), 1);
			if (r->type == REDIR_IN)
				dup2(fd, STDIN_FILENO);
			else
				dup2(fd, STDOUT_FILENO);
			close(fd);
		}
		r = r->next;
	}
	return (0);
}