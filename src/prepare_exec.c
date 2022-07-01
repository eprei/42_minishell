/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olmartin <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 14:51:16 by olmartin          #+#    #+#             */
/*   Updated: 2022/06/30 10:55:41 by olmartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	print_error(t_cmd *cur_cmd)
{
	ft_putstr_fd("Error: ", 2);
	ft_putstr_fd(cur_cmd->full_cmd[0], 2);
	ft_putstr_fd(" : ", 2);
	ft_putendl_fd(cur_cmd->status, 2);
}

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
	else if (ft_strncmp(cur_cmd->full_cmd[0], "exit", 5) == 0)
		;//		ft_exit(1);
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
	g_exit_status = 0;
	cur_cmd = s_pr->cmds;
	if (s_pr->n_cmds == 1)
	{
		if (cur_cmd->status != NULL)
			print_error(cur_cmd);
		else if (cur_cmd->is_builtin == 1)
			res = builtin_is_redir(s_pr, cur_cmd, i);
		else
			prep_exec(s_pr, cur_cmd, i);
	}
	else
	{
		while (cur_cmd != NULL)
		{
			if (cur_cmd->is_builtin == 0)
				res = search_function(s_pr, cur_cmd, i);
			else
				res = builtin_is_redir(s_pr, cur_cmd, i);
			cur_cmd = cur_cmd->next;
			i++;
		}
	}
	g_exit_status = errno;
	return (res);
}

