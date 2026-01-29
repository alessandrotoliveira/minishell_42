/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aletude- <aletude-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 10:52:54 by aletude-          #+#    #+#             */
/*   Updated: 2026/01/29 10:52:56 by aletude-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*newlst;
	t_list	*ptr;
	t_list	*element;

	ptr = lst;
	newlst = NULL;
	while (ptr)
	{
		element = ft_lstnew((*f)(ptr->content));
		if (!element)
		{
			ft_lstclear(&newlst, del);
			return (NULL);
		}
		else
		{
			ft_lstadd_back(&newlst, element);
			ptr = ptr->next;
		}
	}
	return (newlst);
}
