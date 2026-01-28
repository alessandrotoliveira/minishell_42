/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredocs_cleanup.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aletude- <aletude-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 09:15:41 by aletude-          #+#    #+#             */
/*   Updated: 2026/01/26 09:15:41 by aletude-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_heredoc_filename(void)
{
	char		*filename;
	char		*num_str;
	static int	counter = 0;

	num_str = ft_itoa(counter);
	if (!num_str)
		return (NULL);
	filename = ft_strjoin("/tmp/heredoc_", num_str);
	free(num_str);
	return (filename);
}

int	cleanup_on_interrupt(void)
{
	char	*filename;

	filename = get_heredoc_filename();
	if (filename)
	{
		unlink(filename);
		free(filename);
	}
	return (-2);
}
