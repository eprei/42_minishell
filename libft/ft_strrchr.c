/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olmartin <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 10:41:32 by olmartin          #+#    #+#             */
/*   Updated: 2021/11/18 16:29:54 by olmartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strrchr(const char *s, int c)
{
	int		i;

	i = 0;
	while (s[i] != 0)
		i++;
	if (i == 0 && s[i] == (char)c)
		return ((char *)&s[i]);
	else if (i == 0)
		return (0);
	while (i >= 0)
	{
		if (s[i] == (char)c)
			return ((char *)&s[i]);
		else
			i--;
	}
	return (0);
}
