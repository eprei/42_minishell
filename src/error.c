/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epresa-c <epresa-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 10:25:09 by epresa-c          #+#    #+#             */
/*   Updated: 2022/07/12 16:38:11 by epresa-c         ###   ########.fr       */
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
	free(curr->status);
	curr->status = NULL;
	curr->status = ft_strdup(err_msg);
	curr->exec_stat = -1;
	g_exit_status = 1;
	if (ft_strncmp(err_msg, "command not found", 17) == 0 \
	&& ft_strlen(err_msg) == 17)
		g_exit_status = 127;
	else if (ft_strncmp(err_msg, "no such a file or directory", 27) == 0 \
	&& ft_strlen(err_msg) == 27)
		g_exit_status = 1;
	else if (ft_strncmp(err_msg, "is a directory", 14) == 0 && \
	ft_strlen(err_msg) == 14)
		g_exit_status = 126;
}
