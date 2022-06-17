/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epresa-c <epresa-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 15:01:49 by Emiliano          #+#    #+#             */
/*   Updated: 2022/06/16 14:51:35 by epresa-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_exit(int exit_status)
{
	g_exit_status = exit_status;

	if (g_exit_status == 1)
		ft_printf("Error malloc\n");
	// fn_free_t_var;
	// fn_close_fd;
	// fn_free_list_chainee;
			// fn_free_full_cmd
	exit(g_exit_status);
}
