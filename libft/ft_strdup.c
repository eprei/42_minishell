/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olmartin <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 11:32:41 by olmartin          #+#    #+#             */
/*   Updated: 2021/11/18 16:20:28 by olmartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h" 

char	*ft_strdup(const char *s1)
{
	int		i;
	char	*ret;

	i = 0;
	ret = (char *)malloc(sizeof(char) * (ft_strlen(s1) + 1));
	if (ret == NULL)
		return (ret);
	else
	{
		while (s1[i] != 0)
		{
			ret[i] = s1[i];
			i++;
		}
	}
	ret[i] = '\0';
	return (ret);
}
