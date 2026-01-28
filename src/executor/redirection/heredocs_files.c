/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredocs_files.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aletude- <aletude-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 09:16:14 by aletude-          #+#    #+#             */
/*   Updated: 2026/01/26 09:16:14 by aletude-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_heredoc_filename(void)
{
	char		*filename;
	char		*num_str;
	static int	counter = 0;

	num_str = ft_itoa(counter++);
	if (!num_str)
		return (NULL);
	filename = ft_strjoin("/tmp/heredoc_", num_str);
	free(num_str);
	return (filename);
}

static int	open_heredoc_write(char **filename)
{
	int	fd;

	*filename = get_heredoc_filename();
	if (!*filename)
		return (-1);
	fd = open(*filename, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd < 0)
	{
		free(*filename);
		return (-1);
	}
	return (fd);
}

int	create_heredoc_fd(char *delimiter, int expand, t_mini *mini)
{
	struct sigaction	old;
	int					fd_write;
	int					ret;
	char				*filename;

	fd_write = open_heredoc_write(&filename);
	if (fd_write < 0)
		return (-1);
	g_received_signal = 0;
	setup_heredoc_signal(&old);
	ret = write_heredoc_loop(fd_write, delimiter, expand, mini);
	restore_heredoc_signal(&old);
	close(fd_write);
	if (ret)
	{
		unlink(filename);
		free(filename);
		return (-2);
	}
	ret = open(filename, O_RDONLY);
	free(filename);
	return (ret);
}

int	handle_heredoc(char *delimiter)
{
	struct sigaction	old;
	int					fd_write;
	int					ret;
	char				*filename;

	fd_write = open_heredoc_write(&filename);
	if (fd_write < 0)
		return (-1);
	g_received_signal = 0;
	setup_heredoc_signal(&old);
	ret = write_heredoc_loop(fd_write, delimiter, 0, NULL);
	restore_heredoc_signal(&old);
	close(fd_write);
	if (ret || g_received_signal == SIGINT)
	{
		unlink(filename);
		free(filename);
		return (cleanup_on_interrupt());
	}
	ret = open(filename, O_RDONLY);
	free(filename);
	return (ret);
}
