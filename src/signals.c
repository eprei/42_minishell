/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epresa-c <epresa-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 11:44:35 by epresa-c          #+#    #+#             */
/*   Updated: 2022/06/13 17:10:12 by epresa-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	signal_handler(int sig)
{
	if (sig == SIGINT)
	{
		write(1, "\n", 2);

	}
	if (sig == SIGQUIT)
	{
		g_exit_status = 50;
		write(1, "\nExit\n", 7); // search for how to avoid printing ^'\'
		exit(g_exit_status);
	}
}
