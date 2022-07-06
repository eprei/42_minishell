/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Emiliano <Emiliano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 14:51:16 by olmartin          #+#    #+#             */
/*   Updated: 2022/07/06 17:12:47 by olmartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_print_error(t_cmd *cur_cmd)
{
	ft_putstr_fd("Error: ", 2);
	ft_putstr_fd(cur_cmd->full_cmd[0], 2);
	ft_putstr_fd(" : ", 2);
	ft_putendl_fd(cur_cmd->status, 2);
}
/*
int	search_function(t_prompt *s_pr, t_cmd *cur_cmd, int num)
{
	int	res;

	(void)num;
	(void)res;
	res = 0;
		prep_exec(s_pr, cur_cmd, num);
	return (0);
}
*/

int	exec_single(t_prompt *s_pr, t_cmd *cur_cmd, int num)
{
	int	res;

	res = 0;
	if (cur_cmd->status != NULL)
		ft_print_error(cur_cmd);
	else if (cur_cmd->is_builtin == 1)
		res = builtin_is_redir(s_pr, cur_cmd, num);
	else
		prep_exec(s_pr, cur_cmd, num);
	builtin_close_redir(cur_cmd);
	return (0);
}

int	exec_multiple(t_prompt *s_pr, t_cmd *cur_cmd, int num)
{
	int	res;

	res = 0;
	while (cur_cmd != NULL)
	{
		if (cur_cmd->status != NULL) //test a faire sur exec_stat = -1
			ft_print_error(cur_cmd);
		else if (cur_cmd->exec_stat == 1)
		{
			if (cur_cmd->is_builtin == 0)
				prep_exec(s_pr, cur_cmd, num);
			else
				res = builtin_is_redir(s_pr, cur_cmd, num);
		}
		builtin_close_redir(cur_cmd);
		cur_cmd = cur_cmd->next;
		num++;
	}
	return (0);
}

int	read_list(t_prompt *s_pr)
{
	t_cmd	*cur_cmd;
	int		i;
	int		res;

	i = 0;
	res = 0;
	if (s_pr->cmds != NULL)
	{
		cur_cmd = s_pr->cmds;
		if (cur_cmd->exec_stat == 1)
		{
			if (s_pr->n_cmds == 1)
				res = exec_single(s_pr, cur_cmd, i);
			else
				res = exec_multiple(s_pr, cur_cmd, i);
		}
		else
			builtin_close_redir(cur_cmd);
	}
	g_exit_status = errno;
	return (res);
}
