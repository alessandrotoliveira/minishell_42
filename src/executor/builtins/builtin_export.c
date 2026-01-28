/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aletude- <aletude-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 08:55:04 by aletude-          #+#    #+#             */
/*   Updated: 2026/01/26 08:55:04 by aletude-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

static char	**get_key_value_pair(char *arg)
{
	char	**tmp;
	char	*eq_pos;

	eq_pos = ft_strchr(arg, '=');
	tmp = malloc(sizeof(char *) * 3);
	if (!tmp)
		return (NULL);
	tmp[0] = ft_substr(arg, 0, eq_pos - arg);
	tmp[1] = ft_strdup(eq_pos + 1);
	tmp[2] = NULL;
	return (tmp);
}

static void	free_pair(char **pair)
{
	if (!pair)
		return ;
	free(pair[0]);
	free(pair[1]);
	free(pair);
}

int	builtin_export(t_cmd *cmd, t_mini *mini)
{
	int		i;
	char	**pair;
	int		ret;

	ret = 0;
	i = 0;
	if (!cmd->args[++i])
		return (print_export_list(mini->env_list), 0);
	while (cmd->args[i])
	{
		if (!is_valid_identifier(cmd->args[i]))
		{
			ft_putstr_fd("minishell: export: not a valid identifier\n", 2);
			ret = 1;
		}
		else if (ft_strchr(cmd->args[i], '='))
		{
			pair = get_key_value_pair(cmd->args[i]);
			env_set(&mini->env_list, pair[0], pair[1]);
			free_pair(pair);
		}
		i++;
	}
	return (ret);
}

int	is_valid_identifier(char *str)
{
	int	i;

	if (!str || (!ft_isalpha(str[0]) && str[0] != '_'))
		return (0);
	i = 1;
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

void	print_export_list(t_env *env)
{
	while (env)
	{
		ft_putstr_fd("declare -x ", STDOUT_FILENO);
		ft_putstr_fd(env->key, STDOUT_FILENO);
		if (env->value)
		{
			ft_putstr_fd("=\"", STDOUT_FILENO);
			ft_putstr_fd(env->value, STDOUT_FILENO);
			ft_putstr_fd("\"", STDOUT_FILENO);
		}
		ft_putstr_fd("\n", STDOUT_FILENO);
		env = env->next;
	}
}
