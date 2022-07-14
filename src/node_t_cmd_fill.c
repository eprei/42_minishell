/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_t_cmd_fill.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epresa-c <epresa-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 10:25:09 by epresa-c          #+#    #+#             */
/*   Updated: 2022/07/14 17:48:52 by epresa-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	update_index_afer_redir(int redir_stat, int *i, int *j)
{
	if (redir_stat == REDIR_OUTPUT_APPEND || redir_stat == HERE_DOC)
	{
		*i += 2;
		*j += 2;
	}
	if (redir_stat == REDIR_OUTPUT_SIMPLE || redir_stat == REDIR_INPUT)
	{
		*i += 1;
		*j += 1;
	}
}
