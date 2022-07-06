/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olmartin <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 13:56:37 by olmartin          #+#    #+#             */
/*   Updated: 2022/06/28 15:03:15 by olmartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	pwd_builtin(char **my_env)
{
	char	*buffer;

	buffer = NULL;
	buffer = get_env("PWD", my_env);
	if (buffer != NULL)
		ft_putendl_fd(buffer, 0);
	free(buffer);
	return (0);
}

int	exec_cd(char *path, char **my_env)
{
	char	*cur_dir;

	cur_dir = getcwd(NULL, 0);
	if (chdir(path) != 0)
	{	
		g_exit_status = errno;
		perror("Error: cd failed. ");
	}
	else
	{
		set_env("OLDPWD", cur_dir, my_env);
		free(cur_dir);
		cur_dir = getcwd(NULL, 0);
		set_env("PWD", cur_dir, my_env);
		free(cur_dir);
	}
	return (0);
}

int	cd_builtin(t_cmd *cmd, char **my_env)
{
	char	*dest;
	int		len;
	int		res;

	len = ft_strlen(cmd->full_cmd[1]);
	if (ft_strncmp(cmd->full_cmd[1], "~", len) == 0)
		dest = (get_env("HOME", my_env));
	else if (ft_strncmp(cmd->full_cmd[1], "~/", len) == 0)
		dest = (ft_strjoin(get_env("HOME", my_env), cmd->full_cmd[1] + 1));
	else if (ft_strncmp(cmd->full_cmd[1], "-", len) == 0)
	{
		dest = get_env("OLDPWD", my_env);
		if (dest == NULL)
			dest = get_env("PWD", my_env);
	}
	else
		dest = ft_strdup(cmd->full_cmd[1]);
	res = exec_cd(dest, my_env);
	return (res);
}
