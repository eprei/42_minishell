/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prep_builtin_exec.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olmartin <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 15:57:08 by olmartin          #+#    #+#             */
/*   Updated: 2022/06/24 16:18:08 by olmartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	search_builtin(t_prompt *s_pr, t_cmd *cur_cmd, int num)
{
	(void)s_pr;
	(void)num;
	if (ft_strncmp(cur_cmd->full_cmd[0], "cd", 3) == 0 && \
			(cur_cmd->infile != 0 || cur_cmd->outfile != 1))
//		res = cd_builtin(cur_cmd, s_pr->envp);
		printf("builtin-redir\n");
}
