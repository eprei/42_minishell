/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olmartin <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/29 09:12:46 by olmartin          #+#    #+#             */
/*   Updated: 2022/02/23 15:15:13 by olmartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_tab(int n);
static char	*ft_conv(int n, char *tab, int i);

char	*ft_itoa(int n)
{
	char	*tab;

	tab = ft_tab(n);
	if (n == -2147483648)
	{
		tab[0] = '8';
		tab = ft_conv(n / 10, tab, 1);
	}
	else
		tab = ft_conv(n, tab, 0);
	return (ft_rev_tab(tab, ft_strlen(tab)));
}

static char	*ft_tab(int n)
{
	int		nb;
	int		a;
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
	ptr = (char *)malloc(sizeof(char) * (nb + 1));
	if (ptr == 0)
		return (0);
	return (ptr);
}

static char	*ft_conv(int n, char *tab, int i)
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
