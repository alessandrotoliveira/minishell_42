/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aletude- <aletude-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 08:54:57 by aletude-          #+#    #+#             */
/*   Updated: 2026/01/26 08:54:57 by aletude-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"


static int	is_out_of_range(const char *str)
{
	unsigned long long	res;
	int					i;
	int					neg;

	res = 0;
	i = 0;
	neg = 1;
	while (ft_isspace(str[i]))
		i++;
	if (str[i] == '+' || str[i] == '-')
		if (str[i++] == '-')
			neg = -1;
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + (str[i++] - '0');
		if (res > 9223372036854775807ULL && neg == 1)
			return (1);
		if (res > 9223372036854775808ULL && neg == -1)
			return (1);
	}
	return (0);
}

int	builtin_exit(t_cmd *cmd, t_mini *mini)
{
	if (!cmd->args[1])
		if (!mini->cmd_list->next)
			ft_putendl_fd("exit", 2);
	if (!cmd->args[1])
		clean_and_exit(mini, mini->exit_code);
	if (!ft_is_numeric(cmd->args[1]) || is_out_of_range(cmd->args[1]))
	{
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(cmd->args[1], 2);
		ft_putendl_fd(": numeric argument required", 2);
		clean_and_exit(mini, 2);
	}
	if (cmd->args[2])
	{
		ft_putendl_fd("minishell: exit: too many arguments", 2);
		return (mini->exit_code = 1, 1);
	}
	mini->exit_code = ft_atol(cmd->args[1]);
	clean_and_exit(mini, mini->exit_code);
	return (0);
}
