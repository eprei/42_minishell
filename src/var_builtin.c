/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olmartin <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 08:51:32 by olmartin          #+#    #+#             */
/*   Updated: 2022/07/01 16:32:04 by olmartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**export_builtin(t_cmd *cmd, t_prompt *s_pr)
{
	size_t	i;
	char	*name;
	char	*value;	

	i = 0;
	while (cmd->full_cmd[1][i] && cmd->full_cmd[1][i] != '=')
		i++;
	if (i < ft_strlen(cmd->full_cmd[1]))
	{
		name = ft_substr(cmd->full_cmd[1], 0, i);
		value = ft_substr(cmd->full_cmd[1], i + 1, ft_strlen(cmd->full_cmd[1]));
		s_pr->envp = set_env(name, value, s_pr);
	}
	return (s_pr->envp);
}

char	**unset_builtin(char *name, t_prompt *s_pr)
{
	int		is_var;
	char	**ret;
	int		len;

	ret = NULL;
	if (s_pr->envp == 0)
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
		return (ret);
	}
	else
		return (s_pr->envp);
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
	if (cmd->full_cmd[1] == NULL)
		ft_putendl_fd("", 1);
	else if (ft_strncmp(cmd->full_cmd[1], "-n", 3) != 0)
		ft_putendl_fd("", 1);
}