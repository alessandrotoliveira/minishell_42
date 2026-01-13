/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aletude- <aletude-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 09:56:26 by aletude-          #+#    #+#             */
/*   Updated: 2026/01/13 10:48:04 by aletude-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_redirection(t_token_type type)
{
	if (type == REDIR_IN || type == REDIR_OUT
		|| type == APPEND || type == HEREDOC)
		return (1);
	return (0);
}

static void	print_syntax_error(char *token)
{
	ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
	ft_putstr_fd(token, 2);
	ft_putstr_fd("'\n", 2);
}

static int	check_pipe_logic(t_token *curr)
{
	if (!curr->next || curr->next->type == PIPE)
	{
		print_syntax_error("|");
		return (ERROR);
	}
	return (SUCCESS);
}

static int	check_redir_logic(t_token *curr)
{
	if (!curr->next)
	{
		print_syntax_error("newline");
		return (ERROR);
	}
	if (curr->next->type != WORD)
	{
		print_syntax_error(curr->next->content);
		return (ERROR);
	}
	return (SUCCESS);
}

int	check_syntax(t_token *tokens)
{
	t_token	*curr;

	curr = tokens;

	if (curr && curr->type == PIPE)
	{
		print_syntax_error("|");
		return (ERROR);
	}
	while (curr)
	{
		if (curr->type == PIPE)
		{
			if (check_pipe_logic(curr) == ERROR)
				return (ERROR);
		}
		else if (is_redirection(curr->type))
		{
			if (check_redir_logic(curr) == ERROR)
				return (ERROR);
		}
		curr = curr->next;
	}
	return (SUCCESS);
}
