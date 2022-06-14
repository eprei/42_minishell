/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olmartin <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 16:36:37 by olmartin          #+#    #+#             */
/*   Updated: 2022/06/14 16:38:55 by olmartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**init_envp(char **envp)
{
	char	**dest;
	int		i;
	int		len;

	if (!envp)
		return (NULL);
	len = tablen(envp);
	dest = (char **)malloc(sizeof(char *) * (len + 1));
	if (dest == NULL)
		return (NULL);
	i = -1;
	while (++i < len)
	{
		dest[i] = ft_strdup(envp[i]);
		if (dest[i] == NULL)
			return (NULL);
	}
	dest[i] = NULL;
	return (dest);
}
