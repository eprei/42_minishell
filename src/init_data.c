/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epresa-c <epresa-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 16:36:37 by olmartin          #+#    #+#             */
/*   Updated: 2022/06/27 15:12:11 by olmartin         ###   ########.fr       */
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

void	init_path(t_prompt *s_p)
{
	int		i;
	char	*tmp;

	i = 0;
	while (s_p->envp[i] != 0)
	{
		if (ft_strncmp(s_p->envp[i], "PATH=", 5) == 0)
		{
			s_p->paths = ft_split(&s_p->envp[i][5], ':');
			if (s_p->paths == NULL)
				perror("Error with paths.");
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
			perror("Error with paths");
		free(tmp);
	}
}

char	*create_path(char **paths, char *cmdn)
{
	char	*path_cmd;

	path_cmd = ft_strjoin("", cmdn);
	if (access(path_cmd, X_OK) == 0)
		return (path_cmd);
	free(path_cmd);
	while (*paths)
	{
		path_cmd = ft_strjoin(*paths, cmdn);
		if (access(path_cmd, X_OK) == 0)
			return (path_cmd);
		free(path_cmd);
		paths++;
	}
	return (NULL);
}
