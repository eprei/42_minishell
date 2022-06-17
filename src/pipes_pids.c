/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_pids.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olmartin <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 08:47:28 by olmartin          #+#    #+#             */
/*   Updated: 2022/06/17 12:01:56 by olmartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	tab_int_free(int **tab)
{
	int	i;

	i = 0;
	while (tab && tab[i])
	{
		free(tab[i]);
		tab[i] = NULL;
	i++;
	}
}

void	create_pipes_pids(t_prompt *s_pr)
{
	int	i;

	i = 0;
	s_pr->pid = (int *)malloc(sizeof(int) * s_pr->n_cmds);
	if (s_pr->pid == NULL)
		perror("Error: fail to create pids");
	if (s_pr->n_cmds > 1)
	{
		s_pr->pipes = (int **)malloc(sizeof(int *) * (s_pr->n_cmds - 1));
		if (s_pr->pipes == NULL)
			perror("Error: fail to create pipes");
		i = 0;
		while (i < s_pr->n_cmds - 1)
		{
			s_pr->pipes[i] = (int *)malloc(sizeof(int) * 2);
			if (s_pr->pipes[i] == NULL || pipe(s_pr->pipes[i]) != 0)
				perror("Error: fail to create pipes");
			i++;
		}
	}
}

void	close_pipes(t_prompt *s_pr)
{
	int	i;
	int	e;

	i = 0;
	e = 0;
	while (i < s_pr->n_cmds - 1)
	{
		e = close(s_pr->pipes[i][0]);
		e += close(s_pr->pipes[i][1]);
		if (e < 0)
			perror("Error: close pipes failed\n");
		i++;
	}
}
