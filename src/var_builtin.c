/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olmartin <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 08:51:32 by olmartin          #+#    #+#             */
/*   Updated: 2022/06/21 13:25:42 by olmartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	export_builtin(t_cmd *cmd, char **my_env)
{
	int		i;
	char	*name;
	char	*value;	

	i = 0;
	while (cmd->full_cmd[1][i] && cmd->full_cmd[1][i] != '=')
		i++;
	name = ft_substr(cmd->full_cmd[1], 0, i);
	value = ft_substr(cmd->full_cmd[1], i + 1, ft_strlen(cmd->full_cmd[1]));
	return (set_env(name, value, my_env));
}

char	**unset_builtin(char *name, char **my_env)
{
	int		is_var;
	char	**ret;
	int		len;

	ret = NULL;
	if (my_env == 0)
		return (NULL);
	len = tablen(my_env);
	is_var = env_var_exist(name, my_env);
	if (is_var >= 0)
	{
		ret = (char **)malloc(sizeof(char *) * len);
		if (ret == 0)
			return (NULL);
		ret = tab_delone(my_env, ret, is_var);
		tab_free(my_env);
		free(my_env);
	}
	return (ret);
}

void	env_builtin(t_prompt *s_pr)
{
	print_tab(s_pr->envp);
}

void	echo_builtin(t_cmd *cmd)
{
	int	len;
	int	i;

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
	if (ft_strncmp(cmd->full_cmd[1], "-n", 3) != 0)
		ft_putendl_fd("", 1);
}
