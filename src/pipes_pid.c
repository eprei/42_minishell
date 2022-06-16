/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_pid.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olmartin <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 16:55:50 by olmartin          #+#    #+#             */
/*   Updated: 2022/06/16 17:17:02 by olmartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	create_pipes_pids(t_prompt *s_pr)
{
	int	i;

	i = 0;
	s_pr->pipes = (char **)malloc(sizeof(int) * (s_pr->n-cmds - 1));
	if (s_pr->pipes == NULL)
		perror("Error: fail to create pipes");
	s_pr->pids = (char *)malloc(sizeof(int) * s_pr->n-cmds);
	if (s_pr->pids == NULL)
		perror("Error: fail to create pids");
	while (s_pr->pids)
	

	
}
