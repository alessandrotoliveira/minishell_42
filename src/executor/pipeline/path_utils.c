/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aletude- <aletude-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 09:15:18 by aletude-          #+#    #+#             */
/*   Updated: 2026/01/26 09:15:18 by aletude-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*join_and_check(char *path, char *cmd)
{
	char		*tmp;
	char		*full_path;
	struct stat	st;

	tmp = ft_strjoin(path, "/");
	if (!tmp)
		return (NULL);
	full_path = ft_strjoin(tmp, cmd);
	free(tmp);
	if (full_path && access(full_path, F_OK) == 0)
	{
		if (stat(full_path, &st) == 0 && S_ISDIR(st.st_mode))
		{
			free(full_path);
			return (NULL);
		}
		return (full_path);
	}
	free(full_path);
	return (NULL);
}

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

static char	*check_absolute_path(char *cmd)
{
	if (access(cmd, F_OK) != 0)
		return (NULL);
	return (ft_strdup(cmd));
}

char	*find_cmd(char *cmd, char **paths)
{
	int		i;
	char	*res;

	if (!cmd || !*cmd)
		return (NULL);
	if (ft_strchr(cmd, '/'))
		return (check_absolute_path(cmd));
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
