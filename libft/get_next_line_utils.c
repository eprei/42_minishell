/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olmartin <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 17:15:47 by olmartin          #+#    #+#             */
/*   Updated: 2022/02/23 16:34:03 by olmartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int			ft_find_nl(char *over);
static char	*ft_strjoin_gnl(char *s1, char const *s2);

int	ft_find_nl(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (-1);
	while (str[i] != 0)
	{
		if (str[i] != 10)
			i++;
		else
			return (i);
	}
	return (-2);
}

t_struct	*ft_read_join(t_struct *s_gnl, int fd)
{
	char	*buffer;

	buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (buffer == 0)
		s_gnl->ret = -1;
	while (s_gnl->nl_po == -2 && s_gnl->ret > 0)
	{
		s_gnl->ret = read(fd, buffer, BUFFER_SIZE);
		if (s_gnl->ret > 0)
		{
			buffer[s_gnl->ret] = '\0';
			s_gnl->nl_po = ft_find_nl(buffer);
			s_gnl->over = ft_strjoin_gnl
				(s_gnl->over, buffer);
		}		
	}
	free(buffer);
	return (s_gnl);
}

static char	*ft_strjoin_gnl(char *s1, char const *s2)
{
	char	*res;
	int		i;
	int		i2;
	int		l;

	i = 0;
	l = ft_strlen(s1) + ft_strlen(s2) + 1;
	i2 = 0;
	res = (char *)malloc(sizeof(char) * l);
	if (res == 0)
		return (0);
	while (s1[i] != '\0')
	{
		res[i] = s1[i];
		i++;
	}
	free(s1);
	while (s2[i2] != '\0')
	{
		res[i] = s2[i2];
		i++;
		i2++;
	}
	res[i] = '\0';
	return (res);
}
