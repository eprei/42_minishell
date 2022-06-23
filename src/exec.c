/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epresa-c <epresa-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 16:53:57 by olmartin          #+#    #+#             */
/*   Updated: 2022/06/23 14:15:32 by epresa-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	exec_cmd(t_prompt *s_pr, t_cmd *cur_cmd)
{
//	int		dup_res[2];
	int		exec_res;

	printf("in fd et out fd: %d - %d \n", cur_cmd->infile, cur_cmd->outfile);
/*	dup_res[0] = dup2(cur_cmd->outfile, STDOUT_FILENO);
	dup_res[1] = dup2(cur_cmd->infile, STDIN_FILENO);
	if (dup_res[0] < 0 || dup_res[1] < 0)
		perror("Error with dup gen.");
//	close_pipes(s_pr);
	close(cur_cmd->outfile);
	close(cur_cmd->infile);
//	close(0);
//	close(1);
*/	exec_res = execve(cur_cmd->full_path, cur_cmd->full_cmd, s_pr->envp);
	if (exec_res == -1)
	{
		perror("Failure with command");
	}
}

void	prep_exec(t_prompt *s_pr, t_cmd *cur_cmd, int num)
{
	g_exit_status = 0;
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
		waitpid(s_pr->pid[num], &g_exit_status, 0);
		if (WIFEXITED(g_exit_status))
			perror("Error: after execve\n");
			//exit_status(g_exit_status, s_pr, 1);
	}
	if (num == 2)
	{
	close_pipes(s_pr);
	}
}

int	search_function(t_prompt *s_pr, t_cmd *cur_cmd, int num)
{
	int res;

	(void)num;
	res = 0;
	if (ft_strncmp(cur_cmd->full_cmd[0], "cd", 3) == 0)
		res = cd_builtin(cur_cmd, s_pr->envp);
	else if (ft_strncmp(cur_cmd->full_cmd[0], "echo", 5) == 0)
		echo_builtin(cur_cmd);
	else if (ft_strncmp(cur_cmd->full_cmd[0], "env", 4) == 0)
		env_builtin(s_pr);
	else if (ft_strncmp(cur_cmd->full_cmd[0], "exit", 5) == 0)
		;//	fonction a creer
	else if (ft_strncmp(cur_cmd->full_cmd[0], "export", 7) == 0)
		res = export_builtin(cur_cmd, s_pr->envp);
	else if (ft_strncmp(cur_cmd->full_cmd[0], "pwd", 4) == 0)
		res = pwd_builtin(s_pr->envp);
	else if (ft_strncmp(cur_cmd->full_cmd[0], "unset", 6) == 0)
		s_pr->envp = unset_builtin(cur_cmd->full_cmd[1], s_pr->envp);
	else
		prep_exec(s_pr, cur_cmd, num);
		// prep_child2(cur_cmd, s_pr);
	//printf("Res: %d\n", res);
	return (0);
}
