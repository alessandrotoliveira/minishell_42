/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aletude- <aletude-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 17:17:27 by aletude-          #+#    #+#             */
/*   Updated: 2025/07/31 10:06:41 by aletude-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	b;
	size_t	l;

	if (little[0] == '\0')
		return ((char *)big);
	b = 0;
	while (b < len && big[b] != '\0')
	{
		l = 0;
		while ((b + l) < len && big[b + l] == little[l] && little[l] != '\0')
		l++;
		if (little[l] == '\0')
			return ((char *)&big[b]);
	b++;
	}
	return (NULL);
}
