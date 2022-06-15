/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olmartin <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 16:53:57 by olmartin          #+#    #+#             */
/*   Updated: 2022/06/15 17:02:47 by olmartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	exec_cmd(t_pipex *s_p, t_cmd *cur_cmd)
{
	int		dup_res[2];
	int		exec_res;

	dup_res[0] = dup2(cur_cmd->fd_c_out, STDOUT_FILENO);
	dup_res[1] = dup2(cur_cmd->fd_c_in, STDIN_FILENO);
	if (dup_res[0] < 0 || dup_res[1] < 0)
		ft_error("Error with dup gen.", s_p, 1);
	close(s_p->fd[0]);
	close(s_p->fd[1]);
	close(s_p->fd1[0]);
	close(s_p->fd1[1]);
	exec_res = execve(cur_cmd->path_cmd, cur_cmd->cmd, s_p->env);
	if (exec_res == -1)
	{
		free(cur_cmd->path_cmd);
		ft_error("Failure with command A.", s_p, 0);
	}
}

void	prep_exec(t_cmd *cmd, t_prompt *s_pr)
{
	cur_cmd.path_cmd = create_path(s_p->paths, cur_cmd.cmd[0]);
	if (!cur_cmd.path_cmd)
		ft_error("1 Command not found.", s_p, 1);
	s_p->pid1 = fork();
	if (s_p->pid1 < 0)
		ft_error("Error fork", s_p, 1);
	if (s_p->pid1 == 0)
		exec_cmd(s_p, &cur_cmd);
	else
	{
		waitpid(s_p->pid1, &s_p->wstatus, 0);
		if (WIFEXITED(s_p->wstatus))
			exit_status(s_p->wstatus, s_p, 1);
	}
}
