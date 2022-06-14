/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_tab.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olmartin <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 15:35:38 by olmartin          #+#    #+#             */
/*   Updated: 2022/06/14 17:08:45 by olmartin         ###   ########.fr       */
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
		//test si dup OK ?
		i++;
	}
	dest[i++] = add;
	dest[i] = NULL;
	tab_free(src);
	return (dest);
}

void	tab_free(char **tab)
{
	int	i;

	i = 0;
	while (tab && tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
	tab = NULL;
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
