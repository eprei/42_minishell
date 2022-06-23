/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epresa-c <epresa-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 15:01:49 by Emiliano          #+#    #+#             */
/*   Updated: 2022/06/23 16:58:27 by epresa-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_exit(t_var	*v, t_prompt *prompt)
{
	free_all_tabs_and_prompt(v, prompt);
	ft_printf("exit\n");
	exit(g_exit_status);
}
