/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olmartin <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 14:36:35 by olmartin          #+#    #+#             */
/*   Updated: 2022/02/23 15:16:29 by olmartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_choose_arg(va_list ap, char cur_char);
static int	ft_prep_arg(va_list ap, const char *str);

int	ft_printf(const char *s, ...)
{
	va_list	ap;
	size_t	w_char;
	char	cur_char;

	va_start(ap, s);
	w_char = 0;
	cur_char = *s;
	while (cur_char != 0)
	{
		s++;
		if (cur_char != '%')
		{
			ft_putchar_fd(cur_char, 1);
			w_char++;
			cur_char = *s;
			continue ;
		}
		else
		{
			w_char += ft_prep_arg(ap, s);
			cur_char = *(++s);
		}
	}
	va_end(ap);
	return (w_char);
}

static int	ft_prep_arg(va_list ap, const char *str)
{
	size_t	w_char;
	char	cur_char;

	w_char = 0;
	cur_char = *str;
	w_char += ft_choose_arg(ap, cur_char);
	str++;
	return (w_char);
}

static int	ft_choose_arg(va_list ap, char cur_char)
{
	int	i;

	i = 0;
	if (cur_char == 'c')
		i += ft_printf_c(va_arg(ap, int));
	if (cur_char == 'd')
		i += ft_printf_d(va_arg(ap, int));
	if (cur_char == 'i')
		i += ft_printf_i(va_arg(ap, int));
	if (cur_char == 's')
		i += ft_printf_s((const char *)va_arg(ap, const char *));
	if (cur_char == 'u')
		i += ft_printf_u(va_arg(ap, int));
	if (cur_char == 'x')
		i += ft_printf_x(va_arg(ap, int));
	if (cur_char == 'X')
		i += ft_printf_x_upper(va_arg(ap, int));
	if (cur_char == 'p')
		i += ft_printf_p(va_arg(ap, unsigned long));
	if (cur_char == '%')
	{		
		ft_putchar_fd(37, 1);
		i++;
	}
	return (i);
}
