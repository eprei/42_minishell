/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_x.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olmartin <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 13:58:31 by olmartin          #+#    #+#             */
/*   Updated: 2022/02/23 16:03:20 by olmartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_hexa(char *tab, long nb);
static char	*ft_p_hexa(char *str, unsigned long long int nb);

int	ft_printf_p( long long p)
{
	char	*str;
	size_t	len;

	len = 0;
	str = (char *)malloc(sizeof(char *) * 20);
	if (str == NULL)
		return (0);
	str = ft_p_hexa(str, p);
	ft_putstr_fd("0x", 1);
	len += 2;
	ft_putstr_fd(str, 1);
	len += ft_strlen(str);
	free(str);
	return (len);
}

int	ft_printf_x(long p)
{
	char	*str;
	size_t	len;

	str = (char *)malloc(sizeof(char *) * 20);
	if (str == NULL)
		return (0);
	str = ft_hexa(str, p);
	ft_putstr_fd(str, 1);
	len = ft_strlen(str);
	free(str);
	return (len);
}

int	ft_printf_x_upper(long p)
{
	char	*str;
	size_t	len;
	int		i;

	str = (char *)malloc(sizeof(char *) * 20);
	if (str == NULL)
		return (0);
	str = ft_hexa(str, p);
	i = 0;
	while (str[i] != 0)
	{
		str[i] = ft_toupper(str[i]);
		i++;
	}
	ft_putstr_fd(str, 1);
	len = ft_strlen(str);
	free(str);
	return (len);
}

static char	*ft_hexa(char *str, long nb)
{
	size_t	len;

	if (nb < 0)
		nb = nb + 4294967296;
	else if (nb > 4294967295)
		nb = 4294967295;
	str = ft_conv_hexa(str, nb);
	len = ft_strlen(str);
	str = ft_rev_tab(str, len);
	return (str);
}

static char	*ft_p_hexa(char *str, unsigned long long int nb)
{
	size_t	len;

	str = ft_conv_hexa(str, nb);
	len = ft_strlen(str);
	str = ft_rev_tab(str, len);
	return (str);
}
