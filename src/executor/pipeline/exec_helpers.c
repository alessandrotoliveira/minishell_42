/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_helpers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aletude- <aletude-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 09:11:05 by aletude-          #+#    #+#             */
/*   Updated: 2026/01/26 09:11:05 by aletude-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_if_directory(char *path)
{
	struct stat	path_stat;

	if (stat(path, &path_stat) == 0)
	{
		if (S_ISDIR(path_stat.st_mode))
		{
			ft_putstr_fd(path, 2);
			ft_putendl_fd(": Is a directory", 2);
			return (1);
		}
	}
	return (0);
}

void	print_cmd_not_found(char *cmd)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd, 2);
	if (ft_strchr(cmd, '/'))
		ft_putendl_fd(": No such file or directory", 2);
	else
		ft_putendl_fd(": command not found", 2);
}

void	try_exec_as_shell_script(char *path, t_cmd *cmd, char **env_array)
{
	char	**script_args;
	int		i;
	int		argc;

	argc = 0;
	while (cmd->args[argc])
		argc++;
	script_args = malloc(sizeof(char *) * (argc + 2));
	if (script_args)
	{
		script_args[0] = ft_strdup("sh");
		script_args[1] = path;
		i = 1;
		while (cmd->args[i])
		{
			script_args[i + 1] = cmd->args[i];
			i++;
		}
		script_args[i + 1] = NULL;
		execve("/bin/sh", script_args, env_array);
		free(script_args[0]);
		free(script_args);
	}
}

void	handle_execve_error(char *path, char **paths, char **env_array)
{
	perror("minishell: execve error");
	free(path);
	free_array(paths);
	free_array(env_array);
	if (errno == ENOENT)
		exit(127);
	else if (errno == EACCES || errno == EISDIR)
		exit(126);
	exit(1);
}

void	check_path_and_exit(char *path, char **paths, char **env_array)
{
	if (check_if_directory(path))
	{
		free(path);
		free_array(paths);
		free_array(env_array);
		exit(126);
	}
	if (access(path, X_OK) != 0)
	{
		perror(path);
		free(path);
		free_array(paths);
		free_array(env_array);
		exit(126);
	}
}
