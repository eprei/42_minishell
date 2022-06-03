/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olmartin <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 12:10:46 by olmartin          #+#    #+#             */
/*   Updated: 2022/02/23 16:32:43 by olmartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# include "libft.h"
# define GET_NEXT_LINE_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

typedef struct s_struct
{
	char	*ret_li;
	char	*over;
	int		nl_po;
	int		ret;
}			t_struct;
t_struct	*ft_read_join(t_struct *s_gnl, int fd);
#endif
