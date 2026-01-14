/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alessandro <alessandro@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 21:38:33 by alessandro        #+#    #+#             */
/*   Updated: 2026/01/13 21:43:11 by alessandro       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_env_value(t_env *env_list, char *key)
{
	t_env	*curr;
	size_t	len_key;

	curr = env_list;
	len_key = ft_strlen(key);
	while (curr)
	{
		if (ft_strncmp(curr->key, key, len_key) == 0
				&& ft_strlen(curr->key) == len_key)
			return (ft_strdup(curr->value));
		curr = curr->next;
	}
	return (ft_strdup(""));
}
