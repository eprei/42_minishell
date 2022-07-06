/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epresa-c <epresa-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 14:51:16 by olmartin          #+#    #+#             */
/*   Updated: 2022/06/29 10:33:56 by epresa-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	search_function(t_prompt *s_pr, t_cmd *cur_cmd, int num)
{
	int	res;

	(void)num;
	res = 0;
	if (ft_strncmp(cur_cmd->full_cmd[0], "cd", 3) == 0)
		res = cd_builtin(cur_cmd, s_pr->envp);
	else if (ft_strncmp(cur_cmd->full_cmd[0], "echo", 5) == 0)
		echo_builtin(cur_cmd);
	else if (ft_strncmp(cur_cmd->full_cmd[0], "env", 4) == 0)
		env_builtin(s_pr);
	else if (ft_strncmp(cur_cmd->full_cmd[0], "export", 7) == 0)
		s_pr->envp = export_builtin(cur_cmd, s_pr->envp);
	else if (ft_strncmp(cur_cmd->full_cmd[0], "pwd", 4) == 0)
		res = pwd_builtin(s_pr->envp);
	else if (ft_strncmp(cur_cmd->full_cmd[0], "unset", 6) == 0)
		s_pr->envp = unset_builtin(cur_cmd->full_cmd[1], s_pr->envp);
	else
		prep_exec(s_pr, cur_cmd, num);
	return (0);
}

int	read_list(t_prompt *s_pr)
{
	t_cmd	*cur_cmd;
	int		i;
	int		res;

	i = 0;
	res = 0;
	cur_cmd = s_pr->cmds;
	while (cur_cmd != NULL)
	{
		if (cur_cmd->is_builtin == 0)
		{
			res = search_function(s_pr, cur_cmd, i);
		}
		else
		{
			res = builtin_is_redir(s_pr, cur_cmd, i);
		}
		cur_cmd = cur_cmd->next;
		i++;
	}
	return (res);
}

