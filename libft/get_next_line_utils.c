/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alessandro <alessandro@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 12:51:26 by aletude-          #+#    #+#             */
/*   Updated: 2025/10/02 12:54:40 by alessandro       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strleng(const char *str)
{
	int	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

char	*ft_strchrg(const char *s, int c)
{
	unsigned char	cc;

	if (!s)
		return (NULL);
	cc = (unsigned char)c;
	while (*s && *s != cc)
		s++;
	if (*s == cc)
		return ((char *)s);
	return (NULL);
}

char	*ft_strjoing(char const *s1, char const *s2)
{
	char	*result;
	size_t	s1_len;
	size_t	s2_len;
	size_t	j;
	size_t	i;

	if (!s1 && !s2)
		return (NULL);
	s1_len = ft_strleng(s1);
	s2_len = ft_strleng(s2);
	result = malloc(s1_len + s2_len + 1);
	if (!result)
		return (NULL);
	i = 0;
	j = 0;
	while (i < s1_len)
		result[j++] = s1[i++];
	i = 0;
	while (i < s2_len)
		result[j++] = s2[i++];
	result [j] = '\0';
	return (result);
}
