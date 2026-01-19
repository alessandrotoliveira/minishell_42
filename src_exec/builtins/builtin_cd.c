#include "minishell.h"
#include <stdio.h>

static void	update_env_dirs(t_mini *mini, char *new_path)
{
	char	*old_pwd;

	old_pwd = env_get(mini->env_list, "PWD");
	if (old_pwd)
		env_set(&mini->env_list, "OLDPWD", old_pwd);
	env_set(&mini->env_list, "PWD", new_path);
}

int	builtin_cd(t_cmd *cmd, t_mini *mini)
{
	char	*path;
	char	cwd[4096];

	if (cmd->args[1] && cmd->args[2])
	{
		ft_putendl_fd("minishell: cd: too many arguments", 2);
		return (1);
	}
	path = cmd->args[1];
	if (!path || ft_strncmp(path, "~", 2) == 0)
		path = env_get(mini->env_list, "HOME");
	else if (ft_strncmp(path, "-", 2) == 0)
	{
		path = env_get(mini->env_list, "OLDPWD");
		if (!path)
			return (ft_putendl_fd("minishell: cd: OLDPWD not set", 2), 1);
		printf("%s\n", path);
	}
	if (!path || chdir(path) != 0)
	{
		if (!path)
			ft_putendl_fd("minishell: cd: HOME not set", 2);
		else
			perror("minishell: cd");
		return (1);
	}
	return (update_env_dirs(mini, getcwd(cwd, sizeof(cwd))), 0);
}