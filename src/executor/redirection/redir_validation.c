/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_validation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aletude- <aletude-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 09:19:07 by aletude-          #+#    #+#             */
/*   Updated: 2026/01/26 09:19:07 by aletude-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_output_dir_writable(char *file)
{
	char	*dir;
	char	*last_slash;
	int		result;

	dir = ft_strdup(file);
	if (!dir)
		return (0);
	last_slash = ft_strrchr(dir, '/');
	if (last_slash)
		*last_slash = '\0';
	else
	{
		free(dir);
		dir = ft_strdup(".");
		if (!dir)
			return (0);
	}
	result = (access(dir, W_OK) == 0);
	free(dir);
	return (result);
}
