/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_idu.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olmartin <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 15:01:01 by olmartin          #+#    #+#             */
/*   Updated: 2022/02/23 15:16:49 by olmartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_printf_i(const int nb)
{
	char	*str;
	size_t	len;

	str = NULL;
	str = ft_itoa(nb);
	len = ft_strlen(str);
	ft_putstr_fd(str, 1);
	free(str);
	return (len);
}

int	ft_printf_d(const int nb)
{
	char	*str;
	size_t	len;

	str = NULL;
	str = ft_itoa(nb);
	len = ft_strlen(str);
	ft_putstr_fd(str, 1);
	free(str);
	return (len);
}

int	ft_printf_u(const unsigned int nb)
{
	char	*str;
	size_t	len;

	str = NULL;
	str = ft_itoa_printf(nb);
	len = ft_strlen(str);
	ft_putstr_fd(str, 1);
	free(str);
	return (len);
}
