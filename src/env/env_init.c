/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aletude- <aletude-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 21:17:40 by alessandro        #+#    #+#             */
/*   Updated: 2026/01/14 08:09:07 by aletude-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_env	*new_env_node(char *key, char *value)
{
	t_env	*new_node;

	new_node = malloc(sizeof(t_env));
	if (!new_node)
		return (NULL);
	new_node->key = ft_strdup(key);
	if (value)
		new_node->value = ft_strdup(value);
	else
		new_node->value = ft_strdup("");
	new_node->next = NULL;
	return (new_node);
}

static void	env_add_back(t_env **lst, t_env *new_node)
{
	t_env	*curr;

	if (!lst || !new_node)
		return ;
	if (*lst == NULL)
	{
		*lst = new_node;
		return ;
	}
	curr = *lst;
	while (curr->next != NULL)
		curr = curr->next;
	curr->next = new_node;
}

static void	process_env_string(t_env **env_list, char *env_str)
{
	int		i;
	char	*key;
	char	*value;

	i = 0;
	while (env_str[i] && env_str[i] != '=')
		i++;
	key = ft_substr(env_str, 0, i);
	if (env_str[i] == '=')
		value = ft_strdup(&env_str[i + 1]);
	else
		value = ft_strdup("");
	env_add_back(env_list, new_env_node(key, value));
	free(key);
	free(value);
}

void	init_env(t_mini *mini, char **envp)
{
	int	i;

	mini->env_list = NULL;
	if (!envp || !*envp)
		return ;
	i = 0;
	while (envp[i])
	{
		process_env_string(&mini->env_list, envp[i]);
		i++;
	}
}
