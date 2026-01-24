#include "minishell.h"

static char	*get_heredoc_filename(void)
{
	char	*filename;
	char	*pid_str;

	pid_str = ft_itoa(getpid());
	if (!pid_str)
		return (NULL);

	filename = ft_strjoin("/tmp/heredoc_", pid_str);
	free(pid_str);
	return (filename);
}

static int	open_heredoc_temp_file(void)
{
	char	*filename;
	int		fd;

	filename = get_heredoc_filename();
	if (!filename)
		return (-1);

	fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	free(filename);
	return (fd);
}

static int	open_heredoc_read_file(void)
{
	char	*filename;
	int		fd;

	filename = get_heredoc_filename();
	if (!filename)
		return (-1);

	fd = open(filename, O_RDONLY);
	free(filename);
	return (fd);
}

static int	cleanup_on_interrupt(void)
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

int	create_heredoc_fd(char *delimiter)
{
	struct sigaction	old;
	int					fd;
	int					ret;

	fd = open_heredoc_temp_file();
	if (fd < 0)
		return (-1);

	g_received_signal = 0;
	setup_heredoc_signal(&old);
	ret = write_heredoc_loop(fd, delimiter);
	restore_heredoc_signal(&old);
	close(fd);

	if (ret)
	{
		unlink(".heredoc_tmp");
		return (-2);
	}
	return (open_heredoc_read_file());
}

int	handle_heredoc(char *delimiter)
{
	struct sigaction	old;
	int					fd;
	int					ret;

	fd = open_heredoc_temp_file();
	if (fd < 0)
		return (-1);

	g_received_signal = 0;
	setup_heredoc_signal(&old);
	ret = write_heredoc_loop(fd, delimiter);
	restore_heredoc_signal(&old);
	close(fd);

	if (ret || g_received_signal == SIGINT)
		return (cleanup_on_interrupt());
	return (open_heredoc_read_file());
}