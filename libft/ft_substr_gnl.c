/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr_gnl.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olmartin <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 16:03:40 by olmartin          #+#    #+#             */
/*   Updated: 2022/02/23 16:10:11 by olmartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr_gnl(char *s, unsigned int start, size_t len)
{
	char	*res;
	size_t	i;
	size_t	l;
	size_t	mal_l;

	i = start;
	l = 0;
	if (len > ft_strlen(s))
		mal_l = ft_strlen(s) - start + 1;
	else
		mal_l = len + 1;
	res = (char *)malloc(sizeof(char) * mal_l);
	if (res == 0)
		return (0);
	while (s[i] != 0 && l < len)
	{
		res[l] = s[i];
		l++;
		i++;
	}
	res[l] = '\0';
	free(s);
	return (res);
}
