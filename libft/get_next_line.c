/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olmartin <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 12:05:27 by olmartin          #+#    #+#             */
/*   Updated: 2022/02/23 16:28:15 by olmartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static t_struct	*ft_init_struct(t_struct *s_init, char *overflow);
static t_struct	*ft_extract_line(t_struct *s_extr);
static char		*ft_close_struct(t_struct *s_clo);
static char		*ft_check_over(char *over, unsigned int start, int len);

char	*get_next_line(int fd)
{
	static char	*overflow;
	char		*next_line;
	t_struct	*s_gnl;

	if (fd < 0 || BUFFER_SIZE < 0)
		return (NULL);
	s_gnl = (t_struct *)malloc(sizeof(t_struct));
	if (s_gnl == NULL)
		return (NULL);
	s_gnl = ft_init_struct(s_gnl, overflow);
	s_gnl = ft_read_join(s_gnl, fd);
	if (s_gnl->over != NULL)
		s_gnl = ft_extract_line(s_gnl);
	next_line = s_gnl->ret_li;
	overflow = ft_close_struct(s_gnl);
	return (next_line);
}

static t_struct	*ft_init_struct(t_struct *s_init, char *overflow)
{
	s_init->ret_li = NULL;
	s_init->ret = 1;
	if (!overflow)
	{
		s_init->over = (char *)malloc(sizeof(char) * 2);
		if (s_init->over == NULL)
			s_init->ret = -1;
		else
			s_init->over[0] = '\0';
	}
	else
		s_init->over = overflow;
	s_init->nl_po = ft_find_nl(s_init->over);
	return (s_init);
}

static t_struct	*ft_extract_line(t_struct *s_extr)
{
	int		i;

	i = 0;
	if (s_extr->over[0] != '\0')
	{
		s_extr->nl_po = ft_find_nl(s_extr->over);
		if (s_extr->nl_po == -2)
			s_extr->nl_po = ft_strlen(s_extr->over);
		s_extr->ret_li = (char *)malloc(s_extr->nl_po + 2);
		if (s_extr->ret_li == NULL)
			s_extr->ret = -1;
		else
		{
			while (s_extr->over[i] != 0 && i <= s_extr->nl_po)
			{	
				s_extr->ret_li[i] = s_extr->over[i];
				i++;
			}
			s_extr->ret_li[i] = '\0';
		}
	}
	s_extr->over = ft_check_over(s_extr->over, i, BUFFER_SIZE);
	return (s_extr);
}

static char	*ft_close_struct(t_struct *s_clo)
{
	char	*tmp;

	if (s_clo->ret == -1 || (s_clo->ret == 0 && ft_strlen(s_clo->ret_li) == 0))
	{
		s_clo->ret_li = NULL;
		free(s_clo->over);
		s_clo->over = NULL;
		tmp = NULL;
	}
	else
	{
		s_clo->ret_li = NULL;
		tmp = s_clo->over;
		s_clo->over = NULL;
	}
	s_clo->ret = 0;
	s_clo->nl_po = 0;
	free(s_clo);
	return (tmp);
}

static char	*ft_check_over(char *over, unsigned int start, int len)
{
	if (start - ft_strlen(over) == 0)
	{
		free(over);
		return (NULL);
	}
	else
		return (ft_substr_gnl(over, start, len));
}
