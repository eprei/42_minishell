/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_tab.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epresa-c <epresa-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 15:35:38 by olmartin          #+#    #+#             */
/*   Updated: 2022/06/17 16:25:24 by epresa-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	tablen(char **t)
{
	int	i;

	i = 0;
	while (t && t[i])
		i++;
	return (i);
}

char	**tab_add(char **src, char *add)
{
	char	**dest;
	int		len;
	int		i;

	if (!add)
		return (src);
	len = tablen(src);
	dest = (char **)malloc(sizeof(char *) * (len + 2));
	if (dest == NULL)
		return (src);
	i = 0;
	while (i < len)
	{
		dest[i] = ft_strdup(src[i]);
		if (dest[i] == NULL)
			perror("Duplication failed\n");
		i++;
	}
	dest[i++] = ft_strdup(add);
	dest[i] = NULL;
	tab_free(src);
	src = NULL;
	return (dest);
}

void	tab_free(char **tab)
{
	int	i;

	i = 0;
	while (tab && tab[i])
	{
		free(tab[i]);
		tab[i] = NULL;
		i++;
	}
}

void	print_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i] != 0)
	{
		ft_putstr_fd(tab[i++], 1);
		ft_putchar_fd('\n', 1);
	}
}

char	**tab_delone(char **src, char **dest, int to_del)
{
	int	i;
	int	j;
	int	len;

	i = 0;
	j = 0;
	len = tablen(src);
	while (i < len && j < len - 1)
	{
		if (i != to_del)
		{
			dest[j] = ft_strdup(src[i]);
			j++;
		}
		i++;
	}
	dest[j] = NULL;
	return (dest);
}
