/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aletude- <aletude-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 09:21:50 by aletude-          #+#    #+#             */
/*   Updated: 2026/01/26 09:21:50 by aletude-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	handle_in_redir(t_cmd *cmd, t_redir *r)
{
	if (cmd->fd_in != -1)
		close(cmd->fd_in);
	if (r->type == HEREDOC)
	{
		return (1);
	}
	else if (r->type == REDIR_IN)
	{
		cmd->fd_in = open(r->file, O_RDONLY);
		if (cmd->fd_in == -1)
			return (0);
	}
	return (1);
}

static int	handle_out_redir(t_cmd *cmd, t_redir *r)
{
	int	flags;

	if (cmd->fd_out != -1)
		close(cmd->fd_out);
	if (r->type == REDIR_OUT)
		flags = O_CREAT | O_WRONLY | O_TRUNC;
	else
		flags = O_CREAT | O_WRONLY | O_APPEND;
	cmd->fd_out = open(r->file, flags, 0644);
	if (cmd->fd_out == -1)
		return (0);
	return (1);
}

int	handle_cmd_redirs(t_cmd *cmd)
{
	t_redir	*r;

	r = cmd->redirs;
	while (r)
	{
		if (r->type == HEREDOC || r->type == REDIR_IN)
		{
			if (!handle_in_redir(cmd, r))
				return (0);
		}
		else if (r->type == REDIR_OUT || r->type == APPEND)
		{
			if (!handle_out_redir(cmd, r))
				return (0);
		}
		r = r->next;
	}
	return (1);
}

int	validate_redirs(t_cmd *cmd)
{
	t_redir	*r;

	r = cmd->redirs;
	while (r)
	{
		if (r->type == REDIR_IN)
		{
			if (access(r->file, F_OK) != 0)
				return (0);
		}
		else if (r->type == REDIR_OUT || r->type == APPEND)
		{
			if (!check_output_dir_writable(r->file))
				return (0);
		}
		r = r->next;
	}
	return (1);
}

void	handle_cmd_redirs_no_heredoc(t_cmd *cmd)
{
	t_redir	*r;

	r = cmd->redirs;
	while (r)
	{
		if (r->type == REDIR_IN)
		{
			if (!handle_in_redir(cmd, r))
				break ;
		}
		else if (r->type == REDIR_OUT || r->type == APPEND)
		{
			if (!handle_out_redir(cmd, r))
				break ;
		}
		r = r->next;
	}
}
