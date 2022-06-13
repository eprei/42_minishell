/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Emiliano <Emiliano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 11:44:35 by epresa-c          #+#    #+#             */
/*   Updated: 2022/06/10 17:04:47 by Emiliano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../includes/minishell.h"

void ft_new_prompt(int sig)
{
    write(1, "\nHere should be a new prompt\n", 30);
}

void sig_quit(int sig)
{
    write(1, "\nExit\n", 7);
    exit(0);
}