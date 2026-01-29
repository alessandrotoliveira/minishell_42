/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aletude- <aletude-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 09:15:09 by aletude-          #+#    #+#             */
/*   Updated: 2026/01/26 09:15:09 by aletude-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	free_redirs(t_redir *redirs)
{
	t_redir	*tmp;

	while (redirs)
	{
		tmp = redirs->next;
		if (redirs->file)
			free(redirs->file);
		free(redirs);
		redirs = tmp;
	}
}

void	free_commands(t_cmd *cmd)
{
	t_cmd	*tmp;

	while (cmd)
	{
		tmp = cmd->next;
		if (cmd->args)
			free_array(cmd->args);
		if (cmd->redirs)
			free_redirs(cmd->redirs);
		if (cmd->fd_in != -1 && cmd->fd_in != STDIN_FILENO)
			close(cmd->fd_in);
		if (cmd->fd_out != -1 && cmd->fd_out != STDOUT_FILENO)
			close(cmd->fd_out);
		free(cmd);
		cmd = tmp;
	}
}

void	clean_and_exit(t_mini *mini, int exit_code)
{
	if (mini->env_list)
		free_env_list(mini->env_list);
	if (mini->cmd_list)
		free_commands(mini->cmd_list);
	if (mini->tokens)
		free_tokens(&mini->tokens);
	rl_clear_history();
	exit(exit_code);
}

void	free_array(char **arr)
{
	int	i;

	i = 0;
	if (!arr)
		return ;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}
