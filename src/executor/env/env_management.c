/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_management.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aletude- <aletude-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 08:59:35 by aletude-          #+#    #+#             */
/*   Updated: 2026/01/26 08:59:35 by aletude-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_env	*env_new_node(const char *key, const char *value)
{
	t_env	*new;

	new = malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	new->key = ft_strdup(key);
	if (value)
		new->value = ft_strdup(value);
	else
		new->value = NULL;
	new->next = NULL;
	return (new);
}

void	env_set(t_env **env_list, const char *key, const char *value)
{
	t_env	*curr;

	curr = *env_list;
	while (curr)
	{
		if (ft_strcmp(curr->key, key) == 0)
		{
			free(curr->value);
			curr->value = NULL;
			if (value)
				curr->value = ft_strdup(value);
			return ;
		}
		if (!curr->next)
			break ;
		curr = curr->next;
	}
	if (!curr)
		*env_list = env_new_node(key, value);
	else
		curr->next = env_new_node(key, value);
}


void	env_unset(t_env **env_list, const char *key)
{
	t_env	*current;
	t_env	*prev;

	prev = NULL;
	current = *env_list;

	while (current)
	{
		if (ft_strcmp(current->key, key) == 0)
		{
			if (prev)
				prev->next = current->next;
			else
				*env_list = current->next;
			free(current->key);
			free(current->value);
			free(current);
			return ;
		}
		prev = current;
		current = current->next;
	}
}
