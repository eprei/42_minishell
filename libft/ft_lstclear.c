/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olmartin <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 12:15:08 by olmartin          #+#    #+#             */
/*   Updated: 2021/11/24 15:07:29 by olmartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*ptr;
	t_list	*tmp;

	ptr = *lst;
	if (del == 0 || lst == 0)
		return ;
	while (ptr != 0)
	{
		tmp = ptr->next;
		del(ptr->content);
		free(ptr);
		ptr = tmp;
	}
	*lst = 0;
}
