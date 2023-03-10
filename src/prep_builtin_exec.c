/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prep_builtin_exec.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olmartin <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 15:57:08 by olmartin          #+#    #+#             */
/*   Updated: 2022/07/19 09:32:14 by olmartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	search_builtin(t_prompt *s_pr, t_cmd *cur_cmd, int num)
{
	int	res;

	(void)num;
	res = 0;
	if (cur_cmd && cur_cmd->full_cmd[0])
	{
		if (ft_strncmp(cur_cmd->full_cmd[0], "cd", 3) == 0)
			res = cd_builtin(cur_cmd, s_pr);
		else if (ft_strncmp(cur_cmd->full_cmd[0], "echo", 5) == 0)
			echo_builtin(cur_cmd);
		else if (ft_strncmp(cur_cmd->full_cmd[0], "env", 4) == 0)
			env_builtin(s_pr);
		else if (s_pr)
		{
			if (ft_strncmp(cur_cmd->full_cmd[0], "export", 7) == 0)
				s_pr->envp = export_builtin(cur_cmd, s_pr, 0);
			else if (ft_strncmp(cur_cmd->full_cmd[0], "pwd", 4) == 0)
				res = pwd_builtin(s_pr->envp, 1);
			else if (ft_strncmp(cur_cmd->full_cmd[0], "unset", 6) == 0)
				s_pr->envp = unset_builtin(cur_cmd->full_cmd[1], s_pr);
		}
	}
	return (res);
}

int	redir_builtin(t_prompt *s_pr, t_cmd *cur_cmd, int num)
{
	int	dup_res;
	int	res;	

	dup_res = -1;
	if (cur_cmd)
	{
		if (cur_cmd->outfile != 0)
		{
			dup_res = dup2(cur_cmd->outfile, STDOUT_FILENO);
			if (dup_res < 0)
			{
				perror("Error with dup gen.");
				return (1);
			}
		}
		builtin_close_redir(cur_cmd);
		res = search_builtin(s_pr, cur_cmd, num);
		return (res);
	}
	return (1);
}

int	fork_builtin(t_prompt *s_pr, t_cmd *cur_cmd, int num)
{
	int	exitstatus;
	int	pid;

	pid = fork();
	if (pid < 0)
	{
		perror("Error fork");
		return (0);
	}
	if (pid == 0)
	{
		if (redir_builtin(s_pr, cur_cmd, num) == 1)
			g_exit_status = 1;
		exit (g_exit_status);
	}
	else
	{
		waitpid(pid, &exitstatus, 0);
		wait_status(exitstatus);
	}
	builtin_close_redir(cur_cmd);
	return (0);
}

void	builtin_close_redir(t_cmd *cur_cmd)
{
	if (cur_cmd)
	{	
		if (cur_cmd->infile != 0)
			close(cur_cmd->infile);
		if (cur_cmd->outfile != 1)
			close(cur_cmd->outfile);
	}
}

int	builtin_is_redir(t_prompt *s_pr, t_cmd *cur_cmd, int num)
{
	char	*cmd;

	if (cur_cmd && cur_cmd->full_cmd[0])
	{
		cmd = cur_cmd->full_cmd[0];
		if (ft_strncmp(cmd, "cd", 3) == 0 || ft_strncmp(cmd, "unset", 6) == 0)
		{
			builtin_close_redir(cur_cmd);
			return (search_builtin(s_pr, cur_cmd, num));
		}
		else if (cur_cmd->outfile != 1)
			return (fork_builtin(s_pr, cur_cmd, num));
		else
			return (search_builtin(s_pr, cur_cmd, num));
	}
	else
		return (1);
}
