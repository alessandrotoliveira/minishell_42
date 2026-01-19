#include "minishell.h"

static void	write_heredoc(int fd, char *delimiter)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (!line)
		{
			ft_putstr_fd("minishell: warning: here-document delimited by EOF\n", 2);
			break ;
		}
		if (ft_strcmp(line, delimiter) == 0)
		{
			free(line);
			break ;
		}
		ft_putendl_fd(line, fd);
		free(line);
	}
}

int	handle_heredoc(char *delimiter)
{
	int		fd;
	char	*temp_file;

	temp_file = ".heredoc_tmp";
	fd = open(temp_file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd < 0)
		return (-1);
	write_heredoc(fd, delimiter);
	close(fd);
	fd = open(temp_file, O_RDONLY);
	if (fd < 0)
		return (-1);
	unlink(temp_file); 
	return (fd);
}

int	pre_process_heredocs(t_cmd *cmd)
{
	t_cmd	*curr_c;
	t_redir	*curr_r;

	curr_c = cmd;
	while (curr_c)
	{
		curr_r = curr_c->redirs;
		while (curr_r)
		{
			if (curr_r->type == HEREDOC)
			{
				if (curr_c->fd_in != -1)
					close(curr_c->fd_in);
				curr_c->fd_in = handle_heredoc(curr_r->file);
				if (curr_c->fd_in == -2)
					return (0);
			}
			curr_r = curr_r->next;
		}
		curr_c = curr_c->next;
	}
	return (1);
}