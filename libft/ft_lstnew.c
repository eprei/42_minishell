/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olmartin <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 09:01:40 by olmartin          #+#    #+#             */
/*   Updated: 2021/11/22 17:07:08 by olmartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*begin;

	begin = (t_list *)malloc(sizeof(t_list));
	if (begin == 0)
		return (0);
	begin->content = content;
	begin->next = 0;
	return (begin);
}
