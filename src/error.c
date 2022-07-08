/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epresa-c <epresa-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 10:25:09 by epresa-c          #+#    #+#             */
/*   Updated: 2022/07/08 12:31:04 by epresa-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	fn_echo_error(t_cmd *curr, char *subplit_i, char *err_msg)
{
	tab_free(curr->full_cmd);
	free(curr->full_cmd);
	curr->full_cmd = malloc(sizeof(char *) * 2);
	curr->full_cmd[0] = ft_strdup(subplit_i);
	curr->full_cmd[1] = NULL;
	curr->is_builtin = FALSE;
	curr->status = ft_strdup(err_msg);
	curr->exec_stat = -1;
	// g_exit_status = 1;
}
