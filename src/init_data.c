/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olmartin <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 11:28:52 by olmartin          #+#    #+#             */
/*   Updated: 2022/07/18 12:00:03 by olmartin         ###   ########.fr       */
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
	while (s_p->envp != NULL && s_p->envp[i] != 0)
	{
		if (ft_strncmp(s_p->envp[i], "PATH=", 5) == 0)
		{
			s_p->paths = ft_split(&s_p->envp[i][5], ':');
			if (s_p->paths == NULL)
				perror("Error with paths.");
			i = 0;
			while (s_p->paths[i] != 0)
			{
				tmp = s_p->paths[i];
				s_p->paths[i] = ft_strjoin(tmp, "/");
				if (s_p->paths[i++] == NULL)
					perror("Error with paths");
				free(tmp);
			}
			break ;
		}
		i++;
	}
}

char	*create_path(char **paths, char *cmdn)
{
	char	*path_cmd;

	if (cmdn)
	{
		path_cmd = ft_strjoin("", cmdn);
		if (path_cmd != NULL)
		{
			if (access(path_cmd, X_OK) == 0)
				return (path_cmd);
		}
		free(path_cmd);
		if (paths != NULL)
		{
			while (*paths)
			{
				path_cmd = ft_strjoin(*paths, cmdn);
				if (access(path_cmd, X_OK) == 0)
					return (path_cmd);
				free(path_cmd);
				paths++;
			}
		}
	}
	return (NULL);
}

int	create_pipes(t_prompt *s_pr)
{
	int	i;

	i = 0;
	if (s_pr->n_cmds > 1)
	{
		s_pr->pipes = (int **)malloc(sizeof(int *) * (s_pr->n_cmds - 1));
		if (s_pr->pipes == NULL)
		{
			perror("Error: fail to create pipes");
			return (-1);
		}
		while (i < s_pr->n_cmds - 1)
		{
			s_pr->pipes[i] = (int *)malloc(sizeof(int) * 2);
			if (s_pr->pipes[i] == NULL || pipe(s_pr->pipes[i]) != 0)
			{
				perror("Error: fail to create pipes");
				break ;
			}
			i++;
		}
	}
	else
		s_pr->pipes = NULL;
	return (i);
}
