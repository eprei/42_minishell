/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olmartin <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 14:51:16 by olmartin          #+#    #+#             */
/*   Updated: 2022/06/24 16:18:11 by olmartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	search_function(t_prompt *s_pr, t_cmd *cur_cmd, int num)
{
	int	res;

	(void)num;
	res = 0;
	if (t_cmd->is_builtin == TRUE)
		search_builtin(t_prompt *s_pr, t_cmd *cur, int num);
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
	else
		prep_exec(s_pr, cur_cmd, num);
		// prep_child2(cur_cmd, s_pr);
	//printf("Res: %d\n", res);
	return (0);
}

int	is_with_redir(t_prompt *s_pr, t_cmd *cur_cmd, int num)
{
	if (cur_cmd->infile != 0 || cur_cmd->outfile != 1)
	{
		printf("REdir_fork\n");
		return (0);
		//	return (fork_redir(s_pr, cur_cmd, num));
	}
	else
		return (search_function(s_pr, cur_cmd, num));
}

int	test_complete_cmd(t_prompt *s_pr, t_cmd *cur_cmd, int num)
{
/*	(void)s_pr;
	(void)cur_cmd;
	(void)num;
*/	int	res;

	res = 0;
	printf("Test complete cmd\n");
	cur_cmd->outfile = 3;
/*	if (num == 1)
	{
		 res = open_in_files("sortie1", 0, cur_cmd);
	}
	//res = search_function(s_pr, cur_cmd, num);
*/	res = is_with_redir(s_pr, cur_cmd, num);
	return (res);	 
}

int	read_list(t_prompt *s_pr)
{
	t_cmd	*curr;
	int		i;
	int		res;

	i = 0;
	res = 0;
	create_pipes_pids(s_pr);
	curr = s_pr->cmds;
	while (curr != NULL)
	{
		test_complete_cmd(s_pr, curr, i);
	//res = search_function(s_pr, curr, i);
		curr = curr->next;
		i++;
	}
	return (res);
}
/*
int fork_redir_builtin(t_cmd *cur_cmd)
{
	s_pr->pid_num = fork();
	if (s_pr->pid[num] == 0)
	{
		perror("Error fork");
		return (0);
	}

}*/
