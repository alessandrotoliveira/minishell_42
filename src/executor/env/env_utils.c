/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aletude- <aletude-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 09:06:02 by aletude-          #+#    #+#             */
/*   Updated: 2026/01/26 09:06:02 by aletude-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*env_get(t_env *env, const char *key)
{
	while (env)
	{
		if (ft_strcmp(env->key, key) == 0)
			return (env->value);
		env = env->next;
	}
	return (NULL);
}

static char	*join_key_value(t_env *node)
{
	char	*s_tmp;
	char	*res;

	s_tmp = ft_strjoin(node->key, "=");
	if (!s_tmp)
		return (NULL);
	if (node->value)
		res = ft_strjoin(s_tmp, node->value);
	else
		res = ft_strdup(s_tmp);
	free(s_tmp);
	return (res);
}

char	**convert_env_to_array(t_env *lstenv)
{
	int		count;
	t_env	*tmp;
	char	**arr;
	int		i;

	count = 0;
	tmp = lstenv;
	while (tmp && ++count)
		tmp = tmp->next;
	arr = malloc(sizeof(char *) * (count + 1));
	if (!arr)
		return (NULL);
	i = 0;
	while (lstenv)
	{
		arr[i] = join_key_value(lstenv);
		if (!arr[i])
			return (free_array(arr), NULL);
		lstenv = lstenv->next;
		i++;
	}
	arr[i] = NULL;
	return (arr);
}
