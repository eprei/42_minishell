/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olmartin <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 10:43:31 by olmartin          #+#    #+#             */
/*   Updated: 2021/11/19 16:17:51 by olmartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_delim(char const *s, char c);
static void		ft_cut(char **ptr, const char *s, char c, size_t nb);
static size_t	ft_len_cut(char *s, char c, size_t *start);

char	**ft_split(char const *s, char c)
{
	size_t	nb;
	char	**ptr;

	if (s == 0)
		return (0);
	nb = ft_delim(s, c);
	ptr = (char **)malloc(sizeof(char *) * (nb + 1));
	if (ptr == 0)
		return (0);
	ft_cut(ptr, s, c, nb);
	return (ptr);
}

static size_t	ft_delim(char const *s, char c)
{
	size_t	nb;
	size_t	i;

	nb = 0;
	i = 0;
	while (s[i] != 0 && s[i] == c)
		i++;
	while (s[i] != 0)
	{
		nb++;
		while (s[i] != 0 && s[i] != c)
			i++;
		while (s[i] != 0 && s[i] == c)
			i++;
	}
	return (nb);
}

static void	ft_cut(char **ptr, const char *s, char c, size_t nb)
{
	size_t	start;
	size_t	len;
	size_t	i;
	char	*s2;
	size_t	*st;

	start = 0;
	st = &start;
	s2 = 0;
	i = 0;
	while (i < nb)
	{
		len = ft_len_cut((char *)s, c, st);
		s2 = ft_substr(s, start, len);
		ptr[i] = s2;
		*st = *st + len + 1;
		i++;
	}
	ptr[i] = 0;
}

static size_t	ft_len_cut(char *s2, char c, size_t *start)
{
	size_t	i;
	size_t	n;

	i = *start;
	n = 0;
	while (s2[i] == c)
	{
		i++;
		n++;
	}
	*start += n;
	n = 0;
	while (s2[i] != 0 && s2[i] != c)
	{
		i++;
		n++;
	}
	return (n);
}
