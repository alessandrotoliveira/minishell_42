
#include "minishell.h"

void	free_env_list(t_env *env)
{
	t_env	*tmp;

	while (env)
	{
		tmp = env->next;
		free(env->key);
		free(env->value);
		free(env);
		env = tmp;
	}
}

void	free_commands(t_cmd *cmd)
{
	t_cmd	*tmp;

	while (cmd)
	{
		tmp = cmd->next;
		free(cmd);
		cmd = tmp;
	}
}

void	clean_and_exit(t_mini *mini, int exit_code)
{
	if (mini->env_list)
		free_env_list(mini->env_list);

	if (mini->cmd_list)
		free_commands(mini->cmd_list);

	rl_clear_history();


	exit(exit_code);
}

void	free_array(char **arr)
{
	int	i;

	i = 0;
	if (!arr)
		return ;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}