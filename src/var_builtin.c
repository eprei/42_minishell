/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olmartin <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 08:51:32 by olmartin          #+#    #+#             */
/*   Updated: 2022/06/15 10:10:29 by olmartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	export_builtin(t_cmd *cmd, char **my_env)
{
	int		is_var;
	char	*n_var;

	n_var = ft_strjoin(cmd->full_cmd[1], cmd->full_cmd[2]);
	if (n_var == NULL)
		return (1);
	is_var = env_var_exist(cmd->full_cmd[1], my_env);
	if (is_var == -1)
	{
		my_env = tab_add(my_env, n_var);
	}
	else
	{
		free(my_env[is_var]);
		my_env[is_var] = n_var;
	}
	if (env_var_exist(cmd->full_cmd[1], my_env) == -1)
		return (1);
	else
		return (0);
}

int	unset_builtin(char *name, char **my_env)
{
//	(void)name;
//	(void)my_env;
	int		is_var;
	char	**ret;
	int		len;

	if (my_env == 0)
		return (1);
	len = tablen(my_env);
	is_var = env_var_exist(name, my_env);
if (is_var >= 0)
	{
		ret = (char **)malloc(sizeof(char *) * len);
		if (ret == 0)
				return(1);
		ret  = tab_delone(my_env, ret, is_var);
		tab_free(my_env);
		my_env = ret;
	}
	return (0);
}

void	env_builtin(t_prompt *s_pr)
{
	print_tab(s_pr->envp);
}
