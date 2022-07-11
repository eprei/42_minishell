/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olmartin <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 13:56:37 by olmartin          #+#    #+#             */
/*   Updated: 2022/07/11 15:57:42 by olmartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

	int	pwd_builtin(char **my_env, int fd)
{
	char	*buffer;

	buffer = NULL;
	buffer = get_env("PWD", my_env);
	if (buffer != NULL)
		ft_putendl_fd(buffer, fd);
	free(buffer);
	return (0);
}

int	exec_cd(char *path, t_prompt *s_pr)
{
	char	*cur_dir;

	cur_dir = getcwd(NULL, 0);
	if (chdir(path) != 0)
	{	
		//g_exit_status = errno;
		perror("Error: cd failed. ");
	}
	else
	{
		s_pr->envp = set_env("OLDPWD", cur_dir, s_pr);
		free(cur_dir);
		cur_dir = getcwd(NULL, 0);
		s_pr->envp = set_env("PWD", cur_dir, s_pr);
		free(cur_dir);
	}
	return (0);
}

int	cd_builtin(t_cmd *cmd, t_prompt *s_pr)
{
	char	*dest;
	int		len;
	int		res;

	res = 1;
	if (cmd->full_cmd[1] != NULL)
	{
		len = ft_strlen(cmd->full_cmd[1]);
		if (ft_strncmp(cmd->full_cmd[1], "-", len) == 0)
		{
			dest = get_env("OLDPWD", s_pr->envp);
			if (dest == NULL)
				dest = get_env("PWD", s_pr->envp);
			if (dest == NULL)
				return (res);
		}
		else
			dest = ft_strdup(cmd->full_cmd[1]);
		res = exec_cd(dest, s_pr);
	}
	return (res);
}
