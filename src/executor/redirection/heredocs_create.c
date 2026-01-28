/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredocs_create.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aletude- <aletude-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 09:16:02 by aletude-          #+#    #+#             */
/*   Updated: 2026/01/26 09:16:02 by aletude-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	process_heredoc_redir(t_cmd *cmd, t_redir *redir, t_mini *mini)
{
	if (cmd->fd_in != -1 && cmd->fd_in != STDIN_FILENO)
		close(cmd->fd_in);
	cmd->fd_in = create_heredoc_fd(redir->file, redir->hd_expand, mini);
	if (cmd->fd_in < 0)
		return (0);
	return (1);
}

static int	process_cmd_redirs(t_cmd *cmd, t_mini *mini)
{
	t_redir	*redir;

	redir = cmd->redirs;
	while (redir)
	{
		if (redir->type == HEREDOC)
		{
			if (!process_heredoc_redir(cmd, redir, mini))
				return (0);
		}
		redir = redir->next;
	}
	return (1);
}


static int	count_heredoc_redirs(t_cmd *cmd)
{
	t_redir	*redir;
	int		count;

	count = 0;
	redir = cmd->redirs;
	while (redir)
	{
		if (redir->type == HEREDOC)
			count++;
		redir = redir->next;
	}
	return (count);
}

static int	has_heredoc_redirs(t_cmd *cmd)
{
	return (count_heredoc_redirs(cmd) > 0);
}

int	preprocess_heredocs(t_cmd *cmds, t_mini *mini)
{
	t_cmd	*cmd;

	cmd = cmds;
	while (cmd)
	{
		if (has_heredoc_redirs(cmd))
		{
			if (!process_cmd_redirs(cmd, mini))
				return (0);
		}
		cmd = cmd->next;
	}
	return (1);
}
