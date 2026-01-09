/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aletude- <aletude-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 15:08:46 by aletude-          #+#    #+#             */
/*   Updated: 2025/07/31 10:00:01 by aletude-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t				i;
	const unsigned char	*ptr;
	unsigned char		search;

	i = 0;
	ptr = (unsigned char *) s;
	search = (unsigned char) c;
	while (i < n)
	{
		if (ptr[i] == search)
			return ((void *)&ptr[i]);
		i++;
	}
	return (NULL);
}
