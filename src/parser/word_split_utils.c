/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_split_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aletude- <aletude-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 09:20:31 by aletude-          #+#    #+#             */
/*   Updated: 2026/01/29 09:23:06 by aletude-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_words(char *str)
{
	int	count;
	int	i;
	int	in_word;

	count = 0;
	i = 0;
	in_word = 0;
	while (str[i])
	{
		if (str[i] == ' ' || str[i] == '\t' || str[i] == '\n')
			in_word = 0;
		else if (!in_word)
		{
			in_word = 1;
			count++;
		}
		i++;
	}
	return (count);
}

char	**split_by_spaces(char *str)
{
	char	**words;
	int		i;
	int		j;
	int		start;

	words = malloc(sizeof(char *) * (count_words(str) + 1));
	if (!words)
		return (NULL);
	i = 0;
	j = 0;
	while (str[i])
	{
		while (str[i] && (str[i] == ' ' || str[i] == '\t' || str[i] == '\n'))
			i++;
		if (str[i])
		{
			start = i;
			while (str[i] && str[i] != ' ' && str[i] != '\t' && str[i] != '\n')
				i++;
			words[j++] = ft_substr(str, start, i - start);
		}
	}
	words[j] = NULL;
	return (words);
}

void	link_tokens(t_token *prev, t_token *new_tok, t_token **head)
{
	if (prev)
	{
		prev->next = new_tok;
		new_tok->prev = prev;
	}
	else
	{
		*head = new_tok;
		new_tok->prev = NULL;
	}
}

void	insert_split_tokens(t_token **head, t_token *curr, char **words)
{
	t_token	*new_tok;
	t_token	*prev;
	t_token	*next;
	int		i;

	prev = curr->prev;
	next = curr->next;
	i = 0;
	while (words[i])
	{
		new_tok = new_token(words[i], WORD, NONE);
		if (!new_tok)
			return ;
		link_tokens(prev, new_tok, head);
		prev = new_tok;
		i++;
	}
	if (prev)
		prev->next = next;
	if (next)
		next->prev = prev;
	free(words);
}

void	remove_empty_token(t_mini *mini, t_token *curr)
{
	if (curr->prev)
		curr->prev->next = curr->next;
	else
		mini->tokens = curr->next;
	if (curr->next)
		curr->next->prev = curr->prev;
	free(curr->content);
	free(curr);
}
