/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olmartin <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 18:00:24 by olmartin          #+#    #+#             */
/*   Updated: 2021/11/18 13:05:31 by olmartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	int		i;
	int		start;

	if (!set)
		return ((char *)s1);
	i = 0;
	while (s1[i] != 0 && ft_strchr(set, s1[i]))
		i++;
	start = i;
	i = ft_strlen(s1) - 1;
	while (i >= start && ft_strchr(set, s1[i]))
		i--;
	return (ft_substr(s1, start, i - start + 1));
}
