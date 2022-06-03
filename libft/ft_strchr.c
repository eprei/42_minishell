/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olmartin <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 10:56:16 by olmartin          #+#    #+#             */
/*   Updated: 2021/11/25 09:05:25 by olmartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strchr(const char *s, int c)
{
	int		i;

	i = 0;
	while (s[i] != 0)
	{
		if (s[i] == (char)c)
			return ((char *)&s[i]);
		else
			i++;
	}
	if (s[i] == (char)c)
		return ((char *)&s[i]);
	return (0);
}
