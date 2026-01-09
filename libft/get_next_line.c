/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alessandro <alessandro@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 12:51:29 by aletude-          #+#    #+#             */
/*   Updated: 2025/10/02 12:55:13 by alessandro       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_update_stock(char *stock)
{
	int		i;
	int		j;
	char	*new_stock;

	i = 0;
	while (stock[i] && stock [i] != '\n')
		i++;
	if (!stock[i])
	{
		free(stock);
		return (NULL);
	}
	new_stock = malloc(sizeof(char) * ft_strleng(stock) - i);
	if (!new_stock)
	{
		free(new_stock);
		return (NULL);
	}
	i++;
	j = 0;
	while (stock[i])
		new_stock[j++] = stock[i++];
	new_stock[j] = '\0';
	free(stock);
	return (new_stock);
}

char	*ft_extract_line(char *stock)
{
	int		i;
	char	*line;

	if (!stock || !*stock)
		return (NULL);
	i = 0;
	while (stock[i] && stock[i] != '\n')
		i++;
	line = malloc(i + (stock[i] == '\n') + 1);
	if (!line)
		return (NULL);
	i = 0;
	while (stock[i] && stock [i] != '\n')
	{
		line[i] = stock[i];
		i++;
	}
	if (stock[i] == '\n')
		line [i++] = '\n';
	line[i] = '\0';
	return (line);
}

char	*ft_read_and_stock(int fd, char *stock)
{
	char	*buffer;
	char	*temp;
	int		bytes_read;

	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (free(stock), NULL);
	bytes_read = 1;
	while (!ft_strchrg(stock, '\n') && bytes_read > 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read < 0)
			return (free(stock), free(buffer), NULL);
		if (bytes_read == 0)
			break ;
		buffer[bytes_read] = '\0';
		temp = ft_strjoing(stock, buffer);
		free(stock);
		stock = temp;
	}
	free(buffer);
	if (bytes_read < 0 || (bytes_read == 0 && !stock))
		return (NULL);
	return (stock);
}

char	*get_next_line(int fd)
{
	static char	*stock;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	stock = ft_read_and_stock(fd, stock);
	if (!stock || stock[0] == '\0')
	{
		free(stock);
		stock = NULL;
		return (NULL);
	}
	line = ft_extract_line(stock);
	stock = ft_update_stock(stock);
	return (line);
}
