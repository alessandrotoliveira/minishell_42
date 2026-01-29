/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aletude- <aletude-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 10:54:46 by aletude-          #+#    #+#             */
/*   Updated: 2026/01/29 10:54:48 by aletude-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char	*str;
	size_t	len;
	char	find;

	find = (char)c;
	len = ft_strlen(s);
	str = (char *)s;
	if (!s)
		return (NULL);
	while (len + 1 > 0)
	{
		if (*str == find)
			return (str);
		str++;
		len--;
	}	
	return (NULL);
}
