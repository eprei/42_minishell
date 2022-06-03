/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olmartin <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 12:01:26 by olmartin          #+#    #+#             */
/*   Updated: 2021/11/18 11:44:39 by olmartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*res;
	int		i;
	int		l;
	int		mal_l;

	if (ft_strlen(s) < start)
		return (ft_strdup(""));
	i = start;
	l = 0;
	if (len > ft_strlen(s))
		mal_l = ft_strlen(s) - start + 1;
	else
		mal_l = len + 1;
	res = (char *)malloc(sizeof(char) * (mal_l));
	if (res == 0)
		return (0);
	while (s[i] != 0 && l < (int)len)
	{		
		res[l] = s[i];
		l++;
		i++;
	}
	res[l] = '\0';
	return (res);
}
