/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aletude- <aletude-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 18:31:44 by aletude-          #+#    #+#             */
/*   Updated: 2025/07/31 10:03:52 by aletude-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*result;
	int		len_s1;
	int		len_s2;
	int		i;
	int		j;

	if (!s1 || !s2)
		return (NULL);
	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	result = malloc ((len_s1 + len_s2 + 1) * sizeof(char));
	if (!result)
		return (NULL);
	i = -1;
	while (++i < len_s1)
		result[i] = s1[i];
	j = -1;
	while (++j < len_s2)
		result [i + j] = s2[j];
	result [i + j] = '\0';
	return (result);
}
