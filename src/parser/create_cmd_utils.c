/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_cmd_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnanque <bnanque@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 11:02:21 by aletude-          #+#    #+#             */
/*   Updated: 2026/01/27 16:08:35 by bnanque          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*init_new_cmd(void)
{
	t_cmd	*new;

	new = malloc(sizeof(t_cmd));
	if (!new)
		return (NULL);
	new->args = NULL;
	new->redirs = NULL;
	new->fd_in = -1;
	new->fd_out = -1;
	new->next = NULL;
	return (new);
}

void	add_arg_to_cmd(t_cmd *cmd, char *arg)
{
	int		size;
	char	**new_args;
	int		i;

	if (!arg)
		return ;
	size = 0;
	while (cmd->args && cmd->args[size])
		size++;
	new_args = malloc(sizeof(char *) * (size + 2));
	if (!new_args)
		return ;
	i = 0;
	while (i < size)
	{
		new_args[i] = cmd->args[i];
		i++;
	}
	new_args[i] = ft_strdup(arg);
	new_args[i + 1] = NULL;
	if (cmd->args)
		free(cmd->args);
	cmd->args = new_args;
}

void	add_redir_to_cmd(t_cmd *cmd, t_token_type type,
		char *file_name, t_quote quote)
{
	t_redir	*new_redir;
	t_redir	*curr;

	new_redir = malloc(sizeof(t_redir));
	if (!new_redir)
		return ;
	new_redir->type = type;
	new_redir->file = ft_strdup(file_name);
	new_redir->hd_expand = (type == HEREDOC && quote == NONE);
	new_redir->next = NULL;
	if (!cmd->redirs)
		cmd->redirs = new_redir;
	else
	{
		curr = cmd->redirs;
		while (curr->next)
			curr = curr->next;
		curr->next = new_redir;
	}
}

void	cmd_add_back(t_cmd **lst, t_cmd *new)
{
	t_cmd	*curr;

	if (!*lst)
	{
		*lst = new;
		return ;
	}
	curr = *lst;
	while (curr->next)
		curr = curr->next;
	curr->next = new;
}
