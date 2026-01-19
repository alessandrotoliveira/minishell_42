#include "minishell.h"

int	is_builtin(char *cmd)
{
	if (!cmd)
		return (0);
	if (ft_strcmp(cmd, "echo") == 0 || ft_strcmp(cmd, "cd") == 0
		|| ft_strcmp(cmd, "pwd") == 0 || ft_strcmp(cmd, "export") == 0
		|| ft_strcmp(cmd, "unset") == 0 || ft_strcmp(cmd, "env") == 0
		|| ft_strcmp(cmd, "exit") == 0)
		return (1);
	return (0);
}

void	execute_builtin(t_cmd *cmd, t_mini *mini)
{
	char	*name;

	name = cmd->args[0];
	if (ft_strcmp(name, "echo") == 0)
		mini->exit_code = builtin_echo(cmd);
	else if (ft_strcmp(name, "pwd") == 0)
		mini->exit_code = builtin_pwd(cmd);
	else if (ft_strcmp(name, "env") == 0)
		mini->exit_code = builtin_env(cmd, mini);
	else if (ft_strcmp(name, "cd") == 0)
		mini->exit_code = builtin_cd(cmd, mini);
	else if (ft_strcmp(name, "export") == 0)
		mini->exit_code = builtin_export(cmd, mini);
	else if (ft_strcmp(name, "unset") == 0)
		mini->exit_code = builtin_unset(cmd, mini);
	else if (ft_strcmp(name, "exit") == 0)
		mini->exit_code = builtin_exit(cmd, mini);
}

/* ** 1. Junta o path e o comando, verifica se é executável.
*/
static char	*join_and_check(char *path, char *cmd)
{
	char	*tmp;
	char	*full_path;

	tmp = ft_strjoin(path, "/");
	if (!tmp)
		return (NULL);
	full_path = ft_strjoin(tmp, cmd);
	free(tmp);
	if (full_path && access(full_path, X_OK) == 0)
		return (full_path);
	free(full_path);
	return (NULL);
}

/* ** 2. Busca o PATH no ambiente.
*/
char	**get_cmd_paths(t_env *env)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, "PATH") == 0)
		{
			if (!tmp->value)
				return (NULL);
			return (ft_split(tmp->value, ':'));
		}
		tmp = tmp->next;
	}
	return (NULL);
}

/* ** 3. Encontra o comando (usa a join_and_check que ja foi definida acima).
*/
char	*find_cmd(char *cmd, char **paths)
{
	int		i;
	char	*res;

	if (!cmd || !*cmd)
		return (NULL);
	if (ft_strchr(cmd, '/'))
	{
		if (access(cmd, X_OK) == 0)
			return (ft_strdup(cmd));
		return (NULL);
	}
	i = 0;
	while (paths && paths[i])
	{
		res = join_and_check(paths[i], cmd);
		if (res)
			return (res);
		i++;
	}
	return (NULL);
}