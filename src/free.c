/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epresa-c <epresa-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 10:25:09 by epresa-c          #+#    #+#             */
/*   Updated: 2022/07/13 13:56:23 by epresa-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_prev_cmd(t_cmd *curr)
{
	tab_free(curr->prev->full_cmd);
	free(curr->prev->full_cmd);
	curr->prev->full_cmd = NULL;
	free(curr->prev->full_path);
	curr->prev->full_path = NULL;
	free(curr->prev->status);
	curr->prev->status = NULL;
	free(curr->prev);
	curr->prev = NULL;
}

void	free_t_cmd(t_cmd **cmd)
{
	t_cmd	*curr;

	curr = *cmd;
	if (*cmd == NULL)
		return ;
	while (curr->next != NULL)
	{
		curr = curr->next;
		free_prev_cmd(curr);
	}
	tab_free(curr->full_cmd);
	free(curr->full_cmd);
	curr->full_cmd = NULL;
	free(curr->full_path);
	curr->full_path = NULL;
	free(curr->status);
	curr->status = NULL;
	free(curr);
	*cmd = NULL;
}

void	null_all_tabs_and_prompt(t_var *v, t_prompt *prompt)
{
	v->line = NULL;
	v->split = NULL;
	v->s_split = NULL;
	prompt->paths = NULL;
	prompt->pid = NULL;
}

void	free_all_tabs_and_prompt(t_var *v, t_prompt *prompt)
{
	int	i;

	i = 0;
	free(v->line);
	tab_free(v->split);
	free(v->split);
	tab_free(v->s_split);
	free(v->s_split);
	free_t_cmd(&prompt->cmds);
	tab_free(prompt->paths);
	free(prompt->paths);
	free(prompt->pid);
	null_all_tabs_and_prompt(v, prompt);
	if (prompt->n_cmds > 1)
	{
		while (i < prompt->n_cmds - 1)
		{
			free(prompt->pipes[i]);
			prompt->pipes[i] = NULL;
			i++;
		}
		free(prompt->pipes);
		prompt->pipes = NULL;
	}
	prompt->n_cmds = 1;
}
