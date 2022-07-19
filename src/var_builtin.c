/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olmartin <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 08:51:32 by olmartin          #+#    #+#             */
/*   Updated: 2022/07/19 09:31:21 by olmartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**export_no_arg1(char **my_env, t_cmd *cmd, int type)
{
	char	**env_dup;

	if (type == 2)
	{
		env_dup = tab_dup(cmd->full_cmd, 2);
		tab_free(cmd->full_cmd);
		free(cmd->full_cmd);
		return (env_dup);
	}
	else
	{
		env_dup = tab_dup(my_env, tablen(my_env));
		tab_sort(env_dup);
		print_tab_export(env_dup);
		tab_free(env_dup);
		free(env_dup);
	}
	return (NULL);
}

char	**export_builtin(t_cmd *cmd, t_prompt *s_pr, size_t i)
{
	char	*name;
	char	*value;	

	if (!cmd->full_cmd[1])
		export_no_arg1(s_pr->envp, cmd, 1);
	else
	{
		if (cmd->full_cmd[2])
			cmd->full_cmd = export_no_arg1(s_pr->envp, cmd, 2);
		while (cmd->full_cmd[1][i] && cmd->full_cmd[1][i] != '=')
			i++;
		if (i < ft_strlen(cmd->full_cmd[1]))
		{
			if (cmd->full_cmd[2])
				cmd->full_cmd = export_no_arg1(s_pr->envp, cmd, 2);
			name = ft_substr(cmd->full_cmd[1], 0, i);
			value = ft_substr(cmd->full_cmd[1], i + 1, \
			ft_strlen(cmd->full_cmd[1]));
			if (name != NULL && value != NULL)
				s_pr->envp = set_env(name, value, s_pr);
			free(name);
			free(value);
		}
	}
	return (s_pr->envp);
}

char	**unset_builtin(char *name, t_prompt *s_pr)
{
	int		is_var;
	char	**ret;
	int		len;

	ret = NULL;
	if (s_pr == NULL || s_pr->envp == 0)
		return (NULL);
	len = tablen(s_pr->envp);
	is_var = env_var_exist(name, s_pr->envp);
	if (is_var >= 0)
	{
		ret = (char **)malloc(sizeof(char *) * len);
		if (ret == 0)
			return (NULL);
		ret = tab_delone(s_pr->envp, ret, is_var);
		tab_free(s_pr->envp);
		free(s_pr->envp);
		s_pr->envp = NULL;
		return (ret);
	}
	else
		return (s_pr->envp);
}

void	env_builtin(t_prompt *s_pr)
{
	if (s_pr && s_pr->envp)
		print_tab(s_pr->envp);
}

void	echo_builtin(t_cmd *cmd)
{
	int	len;
	int	i;

	if (cmd && cmd->full_cmd)
	{
		len = tablen(cmd->full_cmd);
		i = 1;
		while (i < len && ft_strncmp(cmd->full_cmd[i], "-n", 3) == 0)
			i++;
		while (cmd->full_cmd[i] != NULL)
		{
			ft_putstr_fd(cmd->full_cmd[i], 1);
			if (++i < len)
				ft_putstr_fd(" ", 1);
		}
		if (cmd->full_cmd[1] == NULL)
			ft_putendl_fd("", 1);
		else if (ft_strncmp(cmd->full_cmd[1], "-n", 3) != 0)
			ft_putendl_fd("", 1);
	}
}
