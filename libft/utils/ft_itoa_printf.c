/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_printf.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olmartin <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 12:47:17 by olmartin          #+#    #+#             */
/*   Updated: 2022/02/23 15:20:06 by olmartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static char	*ft_tab(long n);
static char	*ft_conv(long n, char *tab, int i);

char	*ft_itoa_printf(long n)
{
	char	*tab;

	tab = ft_tab(n);
	tab = ft_conv(n, tab, 0);
	return (ft_rev_tab(tab, ft_strlen(tab)));
}

static char	*ft_tab(long n)
{
	long	nb;
	long	a;
	char	*ptr;

	nb = 0;
	a = n;
	while (a != 0)
	{
		a = a / 10;
		nb++;
	}
	if (n < 0)
		nb++;
	else if (n == 0)
		nb++;
	ptr = (char *)malloc(sizeof(char) * (100 + 1));
	if (ptr == 0)
		return (0);
	return (ptr);
}

static char	*ft_conv(long n, char *tab, int i)
{
	int	s;

	if (n < 0)
	{
		s = -1;
		n = -n;
	}
	else
		s = 1;
	while (n > 9)
	{
		tab[i] = (n % 10) + '0';
		i++;
		n = n / 10;
	}
	tab[i++] = n + '0';
	if (s < 0)
		tab[i++] = '-';
	tab[i] = '\0';
	return (tab);
}
