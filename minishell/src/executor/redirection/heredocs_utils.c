#include "minishell.h"

/* ================= RAW INPUT ================= */

static char	*grow_buffer(char *old, size_t old_len)
{
	char	*new;
	size_t	i;

	new = malloc(old_len + 2);
	if (!new)
	{
		free(old);
		return (NULL);
	}
	i = 0;
	while (i < old_len)
	{
		new[i] = old[i];
		i++;
	}
	new[i] = '\0';
	free(old);
	return (new);
}


static char	*append_char(char *line, size_t *len, char c)
{
	char	*new_line;

	new_line = grow_buffer(line, *len);
	if (!new_line)
		return (NULL);
	new_line[*len] = c;
	(*len)++;
	new_line[*len] = '\0';
	return (new_line);
}


static int	read_single_char(char *buffer)
{
	ssize_t	r;

	r = read(STDIN_FILENO, buffer, 1);
	return (r);
}

/*static int	wait_stdin_with_timeout(void)
{
	// Simplified version without select - just return 1 to allow reading
	// The signal handling will take care of interruptions
	return (1);
}
*/
char	*read_heredoc_line(void)
{
	char	buffer;
	char	*line;
	size_t	len;

	line = NULL;
	len = 0;
	while (g_received_signal != SIGINT)
	{
		//if (wait_stdin_with_timeout() <= 0)
			//continue;

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

int	write_heredoc_loop(int fd, char *delimiter)
{
	char	*line;

	while (g_received_signal != SIGINT)
	{
		write(STDOUT_FILENO, "> ", 2);
		line = read_heredoc_line();

		if (g_received_signal == SIGINT)
			break;

		if (!line)
			return (0);

		if (ft_strcmp(line, delimiter) == 0)
		{
			free(line);
			return (0);
		}
		ft_putendl_fd(line, fd);
		free(line);
	}
	return (1);
}