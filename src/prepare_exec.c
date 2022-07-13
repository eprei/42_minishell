/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olmartin <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 14:32:22 by olmartin          #+#    #+#             */
/*   Updated: 2022/07/11 14:20:48 by olmartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_print_error(t_cmd *cur_cmd)
{
	ft_putstr_fd("minishell Error: ", 2);
	ft_putstr_fd(cur_cmd->full_cmd[0], 2);
	ft_putstr_fd(" : ", 2);
	ft_putendl_fd(cur_cmd->status, 2);
	//g_exit_status = 1;
	//printf("errno print error value: %d\n", errno);
}

int	exec_single(t_prompt *s_pr, t_cmd *cur_cmd, int num)
{
	int	res;

	res = 0;
	if (cur_cmd->status != NULL)
	{
		ft_print_error(cur_cmd);
		return (1);
	}
	else if (cur_cmd->full_cmd == NULL || cur_cmd->full_cmd[0] == NULL)
		return (1);
	else if (cur_cmd->exec_stat == 1)
	{
		if (cur_cmd->is_builtin == 1)
			res = builtin_is_redir(s_pr, cur_cmd, num);
		else
			prep_exec(s_pr, cur_cmd, num);
	}
	builtin_close_redir(cur_cmd);
	return (0);
}

int	exec_multiple(t_prompt *s_pr, t_cmd *cur_cmd, int num)
{
	int	res;

	res = 0;
	while (cur_cmd != NULL)
	{
		res = exec_single(s_pr, cur_cmd, num);
/*		if (cur_cmd->status != NULL)
		{
			ft_print_error(cur_cmd);
			return (1);
		}
		else if (cur_cmd->full_cmd[0] == NULL)
			return (1);
		else if (cur_cmd->exec_stat == 1)
		{
			if (cur_cmd->is_builtin == 0)
				prep_exec(s_pr, cur_cmd, num);
			else
				res = builtin_is_redir(s_pr, cur_cmd, num);
		}
*/		builtin_close_redir(cur_cmd);
		cur_cmd = cur_cmd->next;
		num++;
	}
	return (res);
}

int	read_list(t_prompt *s_pr)
{
	t_cmd	*cur_cmd;
	int		i;
	int		res;

	i = 0; //inutile ? 
	res = 1;
	if (s_pr != NULL && s_pr->cmds != NULL)
	{
		cur_cmd = s_pr->cmds;
		if (s_pr->n_cmds == 1)
			res = exec_single(s_pr, cur_cmd, i);
		else
			res = exec_multiple(s_pr, cur_cmd, i);
	}
	g_exit_status = errno;
	return (res);
}
