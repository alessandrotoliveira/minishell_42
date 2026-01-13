/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_manager.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aletude- <aletude-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 07:21:08 by aletude-          #+#    #+#             */
/*   Updated: 2026/01/13 09:03:14 by aletude-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	parse_error(t_mini *mini)
{
	if (mini->tokens)
		free_tokens(&mini->tokens);
	mini->exit_code = 2;
	return (ERROR);
}

static void	process_tokens(t_mini *mini)
{
	expand_variables(mini);
	remove_quotes(mini->tokens);
}

int	parse_input(t_mini *mini, char *input)
{
	if (tokenize_input(mini, input) == ERROR)
		return (parse_error(mini));
	if (mini->tokens == NULL)
		return (SUCCESS);
	if (check_syntax(mini->tokens) == ERROR)
		return (parse_error(mini));
	process_tokens(mini);
	create_cmd_list(mini);
	free_tokens(&mini->tokens);
	return (SUCCESS);
}
