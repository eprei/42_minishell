/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olmartin <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 14:40:33 by olmartin          #+#    #+#             */
/*   Updated: 2022/02/23 15:20:53 by olmartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_conv_hexa(char *tab, unsigned long long int nb)
{
	int	i;
	int	rem;

	i = 0;
	if (nb == 0)
	{
		tab[0] = '0';
		i++;
	}
	else
	{
		while (nb != 0)
		{
			rem = nb % 16;
			if (rem < 10)
				rem += 48;
			else
				rem += 87;
			tab[i] = rem;
			nb /= 16;
			i++;
		}
	}
	tab[i] = '\0';
	return (tab);
}
