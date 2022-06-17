/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olmartin <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 16:53:57 by olmartin          #+#    #+#             */
/*   Updated: 2022/06/17 15:18:25 by olmartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	exec_cmd(t_prompt *s_pr, t_cmd *cur_cmd)
{
	int		dup_res[2];
	int		exec_res;

	dup_res[0] = dup2(cur_cmd->outfile, STDOUT_FILENO);
	dup_res[1] = dup2(cur_cmd->infile, STDIN_FILENO);
	if (dup_res[0] < 0 || dup_res[1] < 0)
		perror("Error with dup gen.");
	close_pipes(s_pr);
	exec_res = execve(cur_cmd->full_path, cur_cmd->full_cmd, s_pr->envp);
	if (exec_res == -1)
	{
		perror("Failure with command");
	}
}

void	prep_exec(t_prompt *s_pr, t_cmd *cur_cmd)
{
	g_exit_status = 0;
	if (!cur_cmd->full_path)
	{
		perror("Command not found.");
		return ;
	}
	s_pr->pid[0] = fork();
	if (s_pr->pid[0] < 0)
	{
		perror("Error fork");
		return ;
	}
	if (s_pr->pid[0] == 0)
		exec_cmd(s_pr, cur_cmd);
	else
	{
		waitpid(s_pr->pid[0], &g_exit_status, 0);
		if (WIFEXITED(g_exit_status))
			perror("Error: after execve\n");
			//exit_status(g_exit_status, s_pr, 1);
	}
}
