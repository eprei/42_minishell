/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Emiliano <Emiliano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 11:44:35 by epresa-c          #+#    #+#             */
/*   Updated: 2022/06/20 11:07:15 by Emiliano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	signal_handler(int sig)
{
	if (sig == SIGINT)
	{
        write(1, "\n", 2);
        rl_on_new_line();
        rl_replace_line("", 1);
        rl_redisplay();
	}
	if (sig == SIGQUIT)
	{
        rl_on_new_line();
        rl_replace_line("", 1);
        rl_redisplay();
	}
}
