/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_cmds.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnanque <bnanque@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 22:06:56 by alessandro        #+#    #+#             */
/*   Updated: 2026/01/27 15:51:31 by bnanque          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_token_action(t_mini *mini, t_token **curr, t_cmd **cmd)
{
	t_token	*tk;

	tk = *curr;
	if (tk->type == PIPE)
	{
		cmd_add_back(&mini->cmd_list, *cmd);
		*cmd = init_new_cmd();
	}
	else if (tk->type == WORD)
	{
		if (tk->content)
			add_arg_to_cmd(*cmd, tk->content);
	}
	else if (tk->type == REDIR_IN || tk->type == REDIR_OUT
		|| tk->type == APPEND)
	{
		add_redir_to_cmd(*cmd, tk->type, tk->next->content, tk->next->quote);
		*curr = tk->next;
	}
	else if (tk->type == HEREDOC)
	{
		add_redir_to_cmd(*cmd, tk->type, tk->next->content, tk->next->quote);
		*curr = tk->next;
	}
}

void	create_commands(t_mini *mini)
{
	t_token	*curr;
	t_cmd	*cmd;

	curr = mini->tokens;
	cmd = init_new_cmd();
	if (!cmd)
		return ;
	while (curr)
	{
		handle_token_action(mini, &curr, &cmd);
		curr = curr->next;
	}
	if (cmd)
		cmd_add_back(&mini->cmd_list, cmd);
}
