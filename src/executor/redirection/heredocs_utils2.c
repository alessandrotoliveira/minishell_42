/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredocs_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aletude- <aletude-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 09:08:22 by aletude-          #+#    #+#             */
/*   Updated: 2026/01/29 09:13:11 by aletude-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	read_single_char(char *buffer)
{
	ssize_t	r;

	r = read(STDIN_FILENO, buffer, 1);
	return (r);
}

char	*read_heredoc_line(void)
{
	char	buffer;
	char	*line;
	size_t	len;

	line = NULL;
	len = 0;
	while (g_received_signal != SIGINT)
	{
		if (read_single_char(&buffer) <= 0)
			return (free(line), NULL);
		if (buffer == '\n')
			return (line);
		line = append_char(line, &len, buffer);
		if (!line)
			return (NULL);
	}
	free(line);
	return (NULL);
}

void	write_heredoc_line(int fd, char *line, int expand, t_mini *mini)
{
	char	*expanded;

	if (expand)
	{
		expanded = expand_line_vars(line, mini);
		ft_putendl_fd(expanded, fd);
		free(expanded);
	}
	else
		ft_putendl_fd(line, fd);
}

int	write_heredoc_loop(int fd, char *delimiter, int expand, t_mini *mini)
{
	char	*line;

	while (g_received_signal != SIGINT)
	{
		write(STDOUT_FILENO, "> ", 2);
		line = read_heredoc_line();
		if (g_received_signal == SIGINT)
			break ;
		if (!line)
			return (0);
		if (ft_strcmp(line, delimiter) == 0)
		{
			free(line);
			return (0);
		}
		write_heredoc_line(fd, line, expand, mini);
		free(line);
	}
	return (1);
}
