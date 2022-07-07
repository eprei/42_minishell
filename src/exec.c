/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epresa-c <epresa-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 16:53:57 by olmartin          #+#    #+#             */
/*   Updated: 2022/07/07 10:59:55 by olmartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	wait_status(int exitstatus)
{
	if (WIFEXITED(exitstatus))
	{
		g_exit_status = WEXITSTATUS(exitstatus);
		if (g_exit_status != 0)
		{
			if (g_exit_status != 255) //sort et CTRL + \ ou CTRL + c
			perror("Error with arguments");
		}
	}
}

void	exec_cmd(t_prompt *s_pr, t_cmd *cur_cmd)
{
	int		dup_res[2];
	int		exec_res;

	//printf("in fd et out fd: %d - %d \n", cur_cmd->infile, cur_cmd->outfile);
	dup_res[0] = dup2(cur_cmd->outfile, STDOUT_FILENO);
	dup_res[1] = dup2(cur_cmd->infile, STDIN_FILENO);
	if (dup_res[0] < 0 || dup_res[1] < 0)
		perror("Error with dup cmd");
	close_pipes(s_pr);
	exec_res = execve(cur_cmd->full_path, cur_cmd->full_cmd, s_pr->envp);
	if (exec_res == -1)
	{
		perror("Failure with command");
		g_exit_status = errno;
	}
}

void	prep_exec(t_prompt *s_pr, t_cmd *cur_cmd, int num)
{
	int	exitstatus;

	s_pr->pid[num] = fork();
	if (s_pr->pid[num] < 0)
	{
		perror("Error fork");
		return ;
	}
	if (s_pr->pid[num] == 0)
		exec_cmd(s_pr, cur_cmd);
	else
	{
		waitpid(s_pr->pid[num], &exitstatus, 0);
		wait_status(exitstatus);
	}
	if (cur_cmd->outfile != 1)
		close(cur_cmd->outfile);
	if (cur_cmd->infile != 0)
		close(cur_cmd->infile);
}
