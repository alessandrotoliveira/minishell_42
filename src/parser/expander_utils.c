/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bnanque <bnanque@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 18:26:30 by alessandro        #+#    #+#             */
/*   Updated: 2026/01/27 14:06:54 by bnanque          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_var_len(char *str)
{
	int	i;

	if (str[0] == '?')
		return (1);
	i = 0;
	while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
		i++;
	return (i);
}

char	*get_token_value(t_mini *mini, char *var_name)
{
	char	*val;

	if (ft_strncmp(var_name, "?", 1) == 0)
		return (ft_itoa(mini->exit_code));
	{
		val = env_get(mini->env_list, var_name);
		if (!val)
			return (ft_strdup(""));
		return (ft_strdup(val));
	}
}
