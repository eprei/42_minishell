/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olmartin <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 11:53:31 by olmartin          #+#    #+#             */
/*   Updated: 2021/11/29 10:31:36 by olmartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static int	ft_nb_blank(char *str);
static void	ft_calc(char c, int *nb, int *s, int *flag);

int	ft_atoi(char *str)
{
	int	i;
	int	s;
	int	nb;
	int	flag;

	s = 1;
	nb = 0;
	flag = 0;
	if (str == 0)
		return (0);
	i = ft_nb_blank(str);
	while (str[i] != 0 && flag < 2)
	{
		if (i > 19 && s == 1)
			return (-1);
		if (i > 18 && s == -1)
			return (0);
		ft_calc(str[i], &nb, &s, &flag);
		i++;
	}
	return (s * nb);
}

static int	ft_nb_blank(char *str)
{
	int	i;

	i = 0;
	while ((str[i] > 8 && str[i] < 14) || str[i] == 32)
	{
		i++;
	}
	return (i);
}

static void	ft_calc(char c, int *nb, int *s, int *flag)
{
	if (c >= '0' && c <= '9')
	{
		*nb = (*nb * 10) + (c - '0');
		*flag = 1;
	}
	else if (c == '-')
	{
		if (*flag == 1)
			*flag = 2;
		else
		{
			*s = *s * -1;
			*flag += 1;
		}
	}
	else if (c == '+')
		*flag += 1;
	else
		*flag = 2;
}
