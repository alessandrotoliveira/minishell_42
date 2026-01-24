/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aletude- <aletude-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 08:41:15 by aletude-          #+#    #+#             */
/*   Updated: 2026/01/15 10:37:47 by aletude-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_matrix(char **matrix)
{
	int	i;

	if (!matrix)
		return ;
	i = 0;
	while (matrix[i])
	{
		free(matrix[i]);
		i++;
	}
	free(matrix);
}

/* UNUSED FUNCTION - Kept for future use
void	free_cmd_list(t_cmd *cmd)
{
	t_cmd	*temp_cmd;
	t_redir	*temp_redir;
	t_redir	*next_redir;

	while (cmd)
	{
		temp_cmd = cmd->next;
		free_matrix(cmd->args);
		temp_redir = cmd->redirs;
		while (temp_redir)
		{
			next_redir = temp_redir->next;
			free(temp_redir->file);
			free(temp_redir);
			temp_redir = next_redir;
		}
		free(cmd);
		cmd = temp_cmd;
	}
}
*/

void	free_env_list(t_env *env)
{
	t_env	*temp;

	while (env)
	{
		temp = env->next;
		free(env->key);
		free(env->value);
		free(env);
		env = temp;
	}
}