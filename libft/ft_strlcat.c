/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olmartin <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 13:59:28 by olmartin          #+#    #+#             */
/*   Updated: 2021/11/18 16:24:01 by olmartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char	*dst, const	char *src, size_t dstsize)
{
	size_t	is;
	size_t	id;
	size_t	lens;
	size_t	lend;

	lens = ft_strlen(src);
	lend = ft_strlen(dst);
	id = lend;
	is = 0;
	if (dstsize <= lend)
		return (lens + dstsize);
	else
	{
		while (src[is] != 0 && is < (dstsize - lend - 1))
		{
			dst[id] = src[is];
			is++;
			id++;
		}
		dst[id] = '\0';
	}
	return (lens + lend);
}
