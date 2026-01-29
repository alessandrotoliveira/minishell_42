/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aletude- <aletude-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 10:58:22 by aletude-          #+#    #+#             */
/*   Updated: 2026/01/29 10:58:24 by aletude-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include "libft.h"
# define BUFFER_SIZE 1048

char	*get_next_line(int fd);

// void	*ft_memcpy(void *dst, const void *src, size_t n);
// char	*ft_strchr(const char *s, int c);
// size_t	ft_strlen(char const *str);
//char	*ft_substr(char const *s, unsigned int start, size_t len, int freeme);
//char	*ft_strjoin(char *s1, char *s2);

#endif
