/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_t_cmd_fill.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Emiliano <Emiliano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 10:25:09 by epresa-c          #+#    #+#             */
/*   Updated: 2022/07/16 16:36:11 by Emiliano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	fill_t_cmd(t_var *v, t_prompt *prompt, int k)
{
	static int	i = 0;
	t_cmd		*curr;
	int			j;
	static int	n_pipe = 0;

	init_vars_fill_t_cmd(k, &j, &n_pipe, &i);
	curr = get_curr_cmd(prompt);
	fill_pipe(v, prompt, &i, &n_pipe);
	while (v->s_split[i] != NULL && v->s_split[i][0] != '|' && \
	curr->exec_stat == EXECUTABLE && prompt->token_status != FAILED)
		fill_redir_and_full_cmd(v, prompt, &i, &j);
	if (curr->full_cmd && ft_strncmp(curr->full_cmd[0], "cd", 2) == 0 && \
		ft_strlen(curr->full_cmd[0]) == 2 && curr->full_cmd[1] == NULL)
		curr->full_cmd = cd_expantion_home(curr, prompt->envp);
	else if (curr->full_cmd && (curr->full_cmd[0][0] == '/' \
	|| (curr->full_cmd[0][0] == '.')))
		fill_slash_and_point(v, prompt, i, j);
	else if (curr->infile != -1 && curr->exec_stat == EXECUTABLE \
	&& curr->full_cmd != NULL)
		search_path(v, prompt, i, j);
	if (v->s_split[i] == NULL)
		i = 0;
}

void	init_vars_fill_t_cmd(int k, int *j, int *n_pipe, int *i)
{
	*j = 0;
	if (k == 0)
		*n_pipe = 0;
	if (k == 0)
		*i = 0;
}

t_cmd	*get_curr_cmd(t_prompt *prompt)
{
	t_cmd	*curr;

	curr = prompt->cmds;
	while (curr->next != NULL)
			curr = curr->next;
	return (curr);
}

void	search_path(t_var *v, t_prompt *prompt, int i, int j)
{
	t_cmd		*curr;

	curr = get_curr_cmd(prompt);
	if (curr->is_builtin == FALSE)
		curr->full_path = create_path(prompt->paths, curr->full_cmd[0]);
	if (curr->full_path == NULL && curr->is_builtin == FALSE)
		fn_echo_error(curr, v->s_split[i - j], "command not found");
}

void	fill_slash_and_point(t_var *v, t_prompt *prompt, int i, int j)
{
	DIR		*dirptr;
	t_cmd	*curr;

	curr = prompt->cmds;
	while (curr->next != NULL)
			curr = curr->next;
	dirptr = opendir(curr->full_cmd[0]);
	if (access(curr->full_cmd[0], F_OK) == 0)
	{
		if (dirptr != NULL)
		{
			fn_echo_error(curr, v->s_split[i - j], "is a directory");
			closedir (dirptr);
			g_exit_status = 126;
		}
		else
			curr->full_path = ft_strdup(curr->full_cmd[0]);
	}
	else
	{
		fn_echo_error(curr, v->s_split[i - j], "No such file or directory");
		g_exit_status = 127;
	}
}
