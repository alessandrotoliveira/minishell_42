/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_split.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnanque <bnanque@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 13:55:32 by bnanque           #+#    #+#             */
/*   Updated: 2026/01/26 13:55:32 by bnanque          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	process_word_token(t_mini *mini, t_token *curr)
{
	char	**words;

	if (!curr->content || curr->content[0] == '\0')
		remove_empty_token(mini, curr);
	else if (count_words(curr->content) > 1)
	{
		words = split_by_spaces(curr->content);
		if (words && words[0])
		{
			insert_split_tokens(&mini->tokens, curr, words);
			free(curr->content);
			free(curr);
		}
	}
}

void	word_splitting(t_mini *mini)
{
	t_token	*curr;
	t_token	*next;

	curr = mini->tokens;
	while (curr)
	{
		next = curr->next;
		if (curr->type == WORD && curr->quote == NONE)
			process_word_token(mini, curr);
		curr = next;
	}
}
