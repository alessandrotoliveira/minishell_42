/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_remover.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alessandro <alessandro@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 19:53:22 by alessandro        #+#    #+#             */
/*   Updated: 2026/01/13 20:07:05 by alessandro       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	change_quote_state(t_quote *quote, char c)
{
	if (*quote == NONE && (c == '\'' || c == '\"'))
	{
		if (c == '\'')
			*quote = SINGLE;
		else
			*quote = DOUBLE;
	}
	else if ((*quote == SINGLE && c == '\'') || (*quote == DOUBLE && c == '\"'))
		*quote = NONE;
}

static char	*remove_quotes_str(char *str)
{
	char	*new_str;
	int		i;
	int		j;
	t_quote	quote;

	new_str = ft_calloc(ft_strlen(str) + 1, sizeof(char));
	if (!new_str)
		return (NULL);
	i = 0;
	j = 0;
	while(str[i])
	{
		if ((quote == NONE && (str[i] == '\'' || str[i] == '\"'))
				|| (quote == SINGLE && str[i] == '\'')
				|| (quote == DOUBLE && str[i] == '\"'))
				change_quote_state(&quote, str[i]);
		else
			new_str[j++] = str[i];
		i++;
	}
	return (new_str);
}

void	remove_quotes(t_mini *mini)
{
	t_token	*curr;
	char	*cleaned;

	curr = mini->tokens;
	while (curr)
	{
		if (curr->type == WORD)
		{
			cleaned = remove_quotes_str(curr->content);
			free(curr->content);
			curr->content = cleaned;
			curr->quote = NONE;
		}
		curr = curr->next;
	}
}
