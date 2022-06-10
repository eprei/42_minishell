/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Emiliano <Emiliano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 11:44:35 by epresa-c          #+#    #+#             */
/*   Updated: 2022/06/10 13:24:17 by Emiliano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../includes/minishell.h"

void ft_new_prompt(int sig)
{
    write(1, "\nHere should be a new prompt\n", 30);
    exit(0);
}

void sig_quit(int sig)
{
    write(1, "\nHere is SIGQUIT\n", 30);
    exit(0);
}