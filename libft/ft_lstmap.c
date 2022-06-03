/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olmartin <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 16:36:50 by olmartin          #+#    #+#             */
/*   Updated: 2021/11/25 08:59:38 by olmartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*ptr;
	t_list	*tmp;

	if (lst == 0 || f == 0 || del == 0)
		return (0);
	ptr = 0;
	while (lst != 0)
	{
		tmp = ft_lstnew((f(lst->content)));
		if (tmp == 0)
		{
			ft_lstclear(&ptr, del);
			return (0);
		}
		ft_lstadd_back(&ptr, tmp);
		lst = lst->next;
	}
	return (ptr);
}
