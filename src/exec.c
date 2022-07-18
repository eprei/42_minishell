/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olmartin <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 11:29:54 by olmartin          #+#    #+#             */
/*   Updated: 2022/07/18 16:33:33 by olmartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	wait_status(int exitstatus)
{
	int	status;

	if (WIFEXITED(exitstatus))
	{
		status = WEXITSTATUS(exitstatus);
		if (status != 0)
		{
			if (status != 255 && errno != 2 && errno != 0)
			{
				perror("Error with arguments");
				printf("errno: %d\n", errno);
				return (errno);
			}
		}
	}
	return (1);
}

void	exec_cmd(t_prompt *s_pr, t_cmd *cur_cmd)
{
	int		dup_res[2];
	int		exec_res;

	echo_ctrl_off();
	signals_default();
	dup_res[0] = dup2(cur_cmd->outfile, STDOUT_FILENO);
	dup_res[1] = dup2(cur_cmd->infile, STDIN_FILENO);
	if (dup_res[0] < 0 || dup_res[1] < 0)
	{
		perror("Error with dup cmd");
		exit (1);
	}
	else
	{
		builtin_close_redir(cur_cmd);
		exec_res = execve(cur_cmd->full_path, cur_cmd->full_cmd, s_pr->envp);
	}
	if (exec_res == -1)
		perror("Failure with command");
	signals_at_start();
	echo_ctrl_on();
}

int	prep_exec(t_prompt *s_pr, t_cmd *cur_cmd, int num)
{
	int	exitstatus;
	int	pid;
	int	res;

	(void)num;
	res = 0;
	errno = 0;
	pid = fork();
	if (pid < 0)
	{
		perror("Error fork");
		return (1);
	}
	if (pid == 0)
		exec_cmd(s_pr, cur_cmd);
	else
	{
		waitpid(pid, &exitstatus, 0);
		res = wait_status(exitstatus);
	}
	if (cur_cmd->outfile != 1)
		close(cur_cmd->outfile);
	if (cur_cmd->infile != 0)
		close(cur_cmd->infile);
	return (res);
}
