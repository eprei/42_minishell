/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olmartin <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/29 17:27:37 by olmartin          #+#    #+#             */
/*   Updated: 2021/11/18 16:28:47 by olmartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *hay, const char *needle, size_t len)
{
	size_t	i_h;
	size_t	i_n;

	i_h = 0;
	if (needle[0] == 0)
		return ((char *)hay);
	while (hay[i_h] != 0 && i_h < len)
	{
		i_n = 0;
		while (hay[i_h + i_n] == needle[i_n])
		{
			if ((needle[i_n + 1] == 0))
				return ((char *)&hay[i_h]);
			else if ((i_h + i_n + 1) >= len)
				return (0);
			i_n++;
		}
		i_h++;
	}
	return (0);
}
