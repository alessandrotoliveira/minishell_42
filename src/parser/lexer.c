/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aletude- <aletude-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 08:15:12 by aletude-          #+#    #+#             */
/*   Updated: 2026/01/14 08:11:28 by aletude-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	append_token(t_mini *mini, char *content, t_token_type type,
			t_quote quote)
{
	t_token	*token;

	if (!content)
		return (0);
	token = new_token(content, type, quote);
	if (!token)
	{
		free(content);
		return (0);
	}
	token_add_back(&mini->tokens, token);
	return (1);
}

static void	update_quote_status(t_quote *quote, char c)
{
	if (*quote == NONE && (c == '\'' || c == '\"'))
	{
		if (c == '\'')
				*quote = SINGLE;
		else
			*quote = DOUBLE;
	}
	else if ((*quote == SINGLE && c == '\'') || \
		(*quote == DOUBLE && c == '\"'))
		*quote = NONE;
}

static int	handle_word(t_mini *mini, char *str)
{
	int		i;
	t_quote	quote;

	i = 0;
	quote = NONE;
	while (str[i])
	{
		update_quote_status(&quote, str[i]);
		if (quote == NONE && (is_whitespace(str[i]) || is_operator(&str[i])))
			break ;
		i++;
	}
	if (quote != NONE)
	{
		printf("minishell: syntax error: unclosed quotes\n");
		return (-1);
	}
	if (!append_token(mini, ft_substr(str, 0, i), WORD, NONE))
		return (-1);
	return (i);
}

static int	handle_operator(t_mini *mini, char *str)
{
	int				len;
	t_token_type	type;

	type = is_operator(str);
	if (type == HEREDOC || type == APPEND)
		len = 2;
	else
		len = 1;
	if (!append_token(mini, ft_substr(str, 0, len), type, NONE))
		return (-1);
	return (len);
}

int	tokenize_input(t_mini *mini, char *input)
{
	int	i;
	int	ret;

	i = 0;
	while (input[i])
	{
		while (is_whitespace(input[i]))
			i++;
		if (!input[i])
			break ;
		if (is_operator(&input[i]))
			ret = handle_operator(mini, &input[i]);
		else
			ret = handle_word(mini, &input[i]);
		if (ret == -1)
		{
			free_tokens(&mini->tokens);
			return (ERROR);
		}
		i += ret;
	}
	return (SUCCESS);
}
