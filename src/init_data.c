/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olmartin <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 16:36:37 by olmartin          #+#    #+#             */
/*   Updated: 2022/06/15 17:14:55 by olmartin         ###   ########.fr       */
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

void	init_path(t_pipex *s_p)
{
	int		i;
	char	*tmp;

	i = 0;
	while (s_p->env[i] != 0)
	{
		if (ft_strncmp(s_p->env[i], "PATH=", 5) == 0)
		{
			s_p->paths = ft_split(&s_p->env[i][5], ':');
			if (s_p->paths == NULL)
				ft_error("Error with paths.", s_p, 1);
			break ;
		}
		i++;
	}
	i = 0;
	while (s_p->paths[i] != 0)
	{
		tmp = s_p->paths[i];
		s_p->paths[i] = ft_strjoin(tmp, "/");
		if (s_p->paths[i++] == NULL)
			ft_error("Error with paths", s_p, 1);
		free(tmp);
	}
}
