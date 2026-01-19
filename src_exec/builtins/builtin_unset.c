#include "minishell.h"
static void	remove_env_node(t_env **env_list, char *key)
{
	t_env	*current;
	t_env	*prev;

	current = *env_list;
	prev = NULL;
	while (current)
	{
		if (ft_strcmp(current->key, key) == 0)
		{
			if (prev == NULL)
				*env_list = current->next;
			else
				prev->next = current->next;
			free(current->key);
			free(current->value);
			free(current);
			return ;
		}
		prev = current;
		current = current->next;
	}
}

int	builtin_unset(t_cmd *cmd, t_mini *mini)
{
	int	i;
	int	exit_code;

	i = 1;
	exit_code = 0;
	if (!cmd->args[i])
		return (0);
	while (cmd->args[i])
	{
		if (!is_valid_identifier(cmd->args[i]))
		{
			ft_putstr_fd("minishell: unset: `", 2);
			ft_putstr_fd(cmd->args[i], 2);
			ft_putendl_fd("': not a valid identifier", 2);
			exit_code = 1;
		}
		else
			remove_env_node(&mini->env_list, cmd->args[i]);
		i++;
	}
	return (exit_code);
}

