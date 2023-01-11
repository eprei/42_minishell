/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_export_tab.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olmartin <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 09:36:39 by olmartin          #+#    #+#             */
/*   Updated: 2022/07/18 15:20:16 by olmartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	print_tab_export(char **tab)
{
	int		i;
	int		j;
	char	*name;

	i = 0;
	while (tab && tab[i] != 0)
	{
		j = 0;
		ft_putstr_fd("declare -x ", 1);
		while (tab[i][j] != '=')
			j++;
		name = ft_substr(tab[i], 0, j + 1);
		ft_putstr_fd(name, 1);
		ft_putchar_fd('"', 1);
		ft_putstr_fd(&tab[i++][j + 1], 1);
		ft_putstr_fd("\"\n", 1);
		free(name);
	}
}

void	ft_swap(char **s1, char **s2)
{
	char	*s3;

	s3 = *s1;
	*s1 = *s2;
	*s2 = s3;
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] != 0 || s2[i] != 0)
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	return (0);
}

void	tab_sort(char **tab)
{
	int	i;
	int	j;

	i = 0;
	j = tablen(tab) - 1;
	if (j > 1)
	{
		while (j > 0)
		{
			while (tab[i + 1])
			{
				if (ft_strcmp(tab[i], tab[i + 1]) > 0)
					ft_swap(&tab[i], &tab[i + 1]);
				i++;
			}
			i = 0;
			j--;
		}
	}
}

char	**tab_dup(char **tab, int len)
{
	int		i;
	char	**dest;

	i = 0;
	dest = (char **)malloc(sizeof(char *) * (len + 1));
	if (dest == NULL)
		return (tab);
	while (i < len)
	{
		dest[i] = ft_strdup(tab[i]);
		i++;
	}
	dest[i] = NULL;
	return (dest);
}
