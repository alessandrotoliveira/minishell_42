#include "minishell.h"

static void	update_env_dirs(t_mini *mini, char *new_path)
{
	char	*old_pwd;

	old_pwd = env_get(mini->env_list, "PWD");
	if (old_pwd)
		env_set(&mini->env_list, "OLDPWD", old_pwd);
	env_set(&mini->env_list, "PWD", new_path);
}

static char	*resolve_cd_path(t_cmd *cmd, t_mini *mini)
{
	char	*path;

	path = cmd->args[1];
	if (!path || ft_strcmp(path, "~") == 0)
	{
		path = env_get(mini->env_list, "HOME");
		if (!path)
			ft_putendl_fd("minishell: cd: HOME not set", 2);
	}
	else if (ft_strcmp(path, "-") == 0)
	{
		path = env_get(mini->env_list, "OLDPWD");
		if (!path)
			ft_putendl_fd("minishell: cd: OLDPWD not set", 2);
		else
			printf("%s\n", path);
	}
	return (path);
}

int	builtin_cd(t_cmd *cmd, t_mini *mini)
{
	char	*path;
	char	cwd[1024];

	if (cmd->args[1] && cmd->args[2])
	{
		ft_putendl_fd("minishell: cd: too many arguments", 2);
		return (1);
	}
	path = resolve_cd_path(cmd, mini);
	if (!path)
		return (1);
	if (chdir(path) != 0)
	{
		perror("minishell: cd");
		return (1);
	}
	if (getcwd(cwd, sizeof(cwd)))
		update_env_dirs(mini, cwd);
	return (0);
}