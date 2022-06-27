/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prep_builtin_exec.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olmartin <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 15:57:08 by olmartin          #+#    #+#             */
/*   Updated: 2022/06/27 12:06:13 by olmartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	search_builtin(t_prompt *s_pr, t_cmd *cur_cmd, int num)
{
	int	res;

	(void)s_pr;
	(void)num;
	res = 0;
	if (ft_strncmp(cur_cmd->full_cmd[0], "cd", 3) == 0)
		res = cd_builtin(cur_cmd, s_pr->envp);
	else if (ft_strncmp(cur_cmd->full_cmd[0], "echo", 5) == 0)
		echo_builtin(cur_cmd);
	else if (ft_strncmp(cur_cmd->full_cmd[0], "env", 4) == 0)
		env_builtin(s_pr);
	else if (ft_strncmp(cur_cmd->full_cmd[0], "export", 7) == 0)
		s_pr->envp = export_builtin(cur_cmd, s_pr->envp);
	else if (ft_strncmp(cur_cmd->full_cmd[0], "pwd", 4) == 0)
		res = pwd_builtin(s_pr->envp);
	else if (ft_strncmp(cur_cmd->full_cmd[0], "unset", 6) == 0)
		s_pr->envp = unset_builtin(cur_cmd->full_cmd[1], s_pr->envp);
	return (res);
}

void redir_builtin(t_prompt *s_pr, t_cmd *cur_cmd, int num)
{
	int		dup_res[2];
	dup_res[0] = -1;
	dup_res[1] = -1;

	printf("in fd et out fd: %d - %d \n", cur_cmd->infile, cur_cmd->outfile);
	if (cur_cmd->infile != 0)
	{
		dup_res[1] = dup2(cur_cmd->infile, STDIN_FILENO);
		if (dup_res[1] < 0)
			perror("Error with dup gen.");
	}
	if (cur_cmd->outfile != 0)
	{
		dup_res[0] = dup2(cur_cmd->outfile, STDOUT_FILENO);
		if (dup_res[0] < 0)
			perror("Error with dup gen.");
	}
	close_pipes(s_pr);
	search_builtin(s_pr, cur_cmd, num);
	if (dup_res[1] != -1)
		close(cur_cmd->infile);
	if (dup_res[0] != -1)
		close(cur_cmd->outfile);
}

int fork_builtin(t_prompt *s_pr, t_cmd *cur_cmd, int num)
{
	int	exitstatus;

	s_pr->pid[num] = fork();
	if (s_pr->pid[num] < 0)
	{
		perror("Error fork");
		return (0);
	}
	if (s_pr->pid[num] == 0)
	{
		redir_builtin(s_pr, cur_cmd, num);
		exit (g_exit_status);
	}
	else
	{
		waitpid(s_pr->pid[num], &exitstatus, 0);
		if (WIFEXITED(exitstatus))
		{
			g_exit_status = WEXITSTATUS(exitstatus);
			if (g_exit_status != 0)
				perror("Error after built");
		}
	}
	if (num == s_pr->n_cmds)
		close_pipes(s_pr);
	return (0);
}

int	builtin_is_redir(t_prompt *s_pr, t_cmd *cur_cmd, int num)
{
	if (cur_cmd->infile != 0 || cur_cmd->outfile != 1)
	{
		printf("REdir_fork\n");
		return (fork_builtin(s_pr, cur_cmd, num));
	}
	else
		return (search_function(s_pr, cur_cmd, num));
}
