/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_t_cmd_fill_redir.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epresa-c <epresa-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 10:25:09 by epresa-c          #+#    #+#             */
/*   Updated: 2022/07/19 12:30:03 by epresa-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	fill_redir_and_full_cmd(t_var	*v, t_prompt *prompt, int *i, int *j)
{
	int		redir_stat;
	t_cmd	*curr;

	curr = prompt->cmds;
	while (curr->next != NULL)
			curr = curr->next;
	redir_stat = FALSE;
	is_redir(v, i, &redir_stat, prompt);
	if (redir_stat != FALSE)
	{
		update_index_afer_redir(redir_stat, i, j);
		fill_cmd_redir(v, i, redir_stat, curr);
	}
	else if (curr->exec_stat == EXECUTABLE)
	{
		curr->full_cmd = tab_add(curr->full_cmd, v->s_split[*i]);
		is_builtin_is_exit(curr, prompt, *i, v);
	}
	*i += 1;
	*j += 1;
}

void	fill_cmd_redir(t_var *v, int *i, int redir_stat, t_cmd *curr)
{
	struct termios	termios_save;
	struct termios	termios_new;
	int				op_rdir_stat;

	op_rdir_stat = FALSE;
	if (redir_stat == REDIR_OUTPUT_APPEND)
		op_rdir_stat = open_outfiles(v->s_split[*i], TRUE, curr);
	else if (redir_stat == REDIR_OUTPUT_SIMPLE)
		op_rdir_stat = open_outfiles(v->s_split[*i], FALSE, curr);
	else if (redir_stat == HERE_DOC)
	{
		tcgetattr(0, &termios_save);
		termios_new = termios_save;
		termios_new.c_lflag &= ~ECHOCTL;
		tcsetattr(0, 0, &termios_new);
		op_rdir_stat = open_in_files(NULL, v->s_split[*i], curr);
		tcsetattr(0, 0, &termios_save);
	}
	else if (redir_stat == REDIR_INPUT)
		op_rdir_stat = open_in_files(v->s_split[*i], NULL, curr);
	if (op_rdir_stat == FALSE)
		fn_echo_error(curr, v->s_split[*i], "no such a file or directory");
}

void	fill_pipe(t_var *v, t_prompt *prompt, int *i, int *n_pipe)
{
	t_cmd		*curr;

	curr = prompt->cmds;
	while (curr->next != NULL)
			curr = curr->next;
	if (v->s_split[*i][0] == '|')
	{
		if (curr->prev->outfile == 1)
		{
			curr->prev->outfile = prompt->pipes[*n_pipe][1];
			curr->infile = prompt->pipes[*n_pipe][0];
		}
		else
		{
			close(prompt->pipes[*n_pipe][1]);
			close(prompt->pipes[*n_pipe][0]);
		}
		*n_pipe = *n_pipe + 1;
		*i += 1;
	}
}

void	update_index_afer_redir(int redir_stat, int *i, int *j)
{
	if (redir_stat == REDIR_OUTPUT_APPEND || redir_stat == HERE_DOC)
	{
		*i += 2;
		*j += 2;
	}
	if (redir_stat == REDIR_OUTPUT_SIMPLE || redir_stat == REDIR_INPUT)
	{
		*i += 1;
		*j += 1;
	}
}
