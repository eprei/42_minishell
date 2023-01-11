/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_s.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olmartin <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 09:31:13 by olmartin          #+#    #+#             */
/*   Updated: 2022/02/23 15:17:05 by olmartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_printf_s(const char *str)
{
	if (str == NULL)
	{
		str = "(null)";
		ft_putstr_fd((char *)str, 1);
	}
	else
		ft_putstr_fd((char *)str, 1);
	return (ft_strlen(str));
}

int	ft_printf_c(const int c)
{
	ft_putchar_fd(c, 1);
	return (1);
}
