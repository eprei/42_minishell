/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termios.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epresa-c <epresa-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 15:01:49 by Emiliano          #+#    #+#             */
/*   Updated: 2022/07/12 16:12:08 by epresa-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	echo_ctrl_on(void)
{
	struct termios	termios_save;
	struct termios	termios_new;

	tcgetattr(0, &termios_save);
	termios_new = termios_save;
	termios_new.c_lflag |= ECHOCTL;
	tcsetattr(0, 0, &termios_new);
}

void	echo_ctrl_off(void)
{
	struct termios	termios_save;
	struct termios	termios_new;

	tcgetattr(0, &termios_save);
	termios_new = termios_save;
	termios_new.c_lflag &= ~ECHOCTL;
	tcsetattr(0, 0, &termios_new);
}
