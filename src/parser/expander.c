/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aletude- <aletude-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 17:58:57 by alessandro        #+#    #+#             */
/*   Updated: 2026/01/29 08:13:52 by aletude-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*replace_str_env(char *old, char *new_val, int pos, int len_name)
{
	char	*prefix;
	char	*suffix;
	char	*temp;
	char	*result;

	prefix = ft_substr(old, 0, pos);
	suffix = ft_substr(old, pos + len_name + 1, ft_strlen(old));
	temp = ft_strjoin(prefix, new_val);
	result = ft_strjoin(temp, suffix);
	free(prefix);
	free(suffix);
	free(temp);
	free(new_val);
	free(old);
	return (result);
}

static void	handle_expansion(t_mini *mini, t_token *token, int *i)
{
	int		len_name;
	char	*var_name;
	char	*var_value;

	len_name = get_var_len(&token->content[*i + 1]);
	if (len_name == 0)
		return ;
	var_name = ft_substr(token->content, *i + 1, len_name);
	var_value = get_token_value(mini, var_name);
	free(var_name);
	token->content = replace_str_env(token->content, var_value, *i, len_name);
	if (ft_strlen(var_value) == 0 && *i > 0)
		*i = *i - 1;
	else
		*i = *i + ft_strlen(var_value) - 1;
}

static void	process_token(t_mini *mini, t_token *curr)
{
	int	i;

	i = 0;
	while (curr->content[i])
	{
		if (curr->content[i] == '$' && curr->content[i + 1] != '\0'
			&& curr->content[i + 1] != ' ')
			handle_expansion(mini, curr, &i);
		i++;
	}
}

void	expand_variables(t_mini *mini)
{
	t_token	*curr;

	curr = mini->tokens;
	while (curr)
	{
		if (curr->type == WORD && curr->quote != SINGLE
			&& ft_strchr(curr->content, '$'))
			process_token(mini, curr);
		curr = curr->next;
	}
}
