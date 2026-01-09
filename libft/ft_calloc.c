/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aletude- <aletude-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 19:11:00 by aletude-          #+#    #+#             */
/*   Updated: 2025/07/31 09:58:06 by aletude-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	size_t	value;
	void	*ptr;

	if (nmemb == 0 || size == 0)
		return (malloc (0));
	if (size != 0 && nmemb > SIZE_MAX / size)
		return (NULL);
	value = nmemb * size;
	ptr = malloc(value);
	if (!ptr)
		return (NULL);
	ft_bzero(ptr, value);
	return (ptr);
}
