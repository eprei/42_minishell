/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Emiliano <Emiliano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 11:44:35 by epresa-c          #+#    #+#             */
/*   Updated: 2022/07/12 11:58:07 by Emiliano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// static mode
void	signal_handler1(int sig)
{
	if (sig == SIGINT)
	{
		write(1, "\n", 2);
		rl_on_new_line();
		rl_replace_line("", 1);
		rl_redisplay();
		g_exit_status = 1;
	}
}

// interactive mode
void	signal_handler2(int sig)
{
	if (sig == SIGINT)
	{
		write(1, "\n", 2);
		rl_on_new_line();
		rl_replace_line("", 1);
		g_exit_status = 1;
	}
}
