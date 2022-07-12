/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epresa-c <epresa-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 10:25:09 by epresa-c          #+#    #+#             */
/*   Updated: 2022/07/12 15:18:08 by epresa-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	print_list(t_prompt *prompt)
{
	t_cmd	*curr;
	int		i;

	i = 0;
	curr = prompt->cmds;
	ft_printf("\n\t**** PRINTING LIST OF COMMANDS ****\n");
	ft_printf("\n\t\tg_status at start = %d\n", g_exit_status);
	while (curr != NULL)
	{
		ft_printf("\ncmd_[%d] \t address = %p\n", i, curr);
		print_tab_with_str_name(curr->full_cmd, "cmd->full_cmd");
		ft_printf("\tfull_path = %s\n", curr->full_path);
		ft_printf("\tinfile = %d\n", curr->infile);
		ft_printf("\toutfile = %d\n", curr->outfile);
		ft_printf("\tis_builtin = %d\n", curr->is_builtin);
		ft_printf("\tstatus = %s\n", curr->status);
		ft_printf("\texec_status = %d\n", curr->exec_stat);
		ft_printf("\tprev = %p\n", curr->prev);
		ft_printf("\tnext = %p\n", curr->next);
		ft_printf("\tg_exit_status = %d\n", g_exit_status);
		curr = curr->next;
		i++;
	}
}
