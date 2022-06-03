/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olmartin <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 14:12:09 by olmartin          #+#    #+#             */
/*   Updated: 2021/11/25 14:46:37 by olmartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*res;
	int		i;
	int		i2;
	int		l;

	i = 0;
	l = ft_strlen(s1) + ft_strlen(s2) + 1;
	i2 = 0;
	res = (char *)malloc(sizeof(char) * l);
	if (res == 0)
		return (0);
	while (s1[i] != '\0')
	{
		res[i] = s1[i];
		i++;
	}
	while (s2[i2] != '\0')
	{
		res[i] = s2[i2];
		i++;
		i2++;
	}
	res[i] = '\0';
	return (res);
}
