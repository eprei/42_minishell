/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_redir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epresa-c <epresa-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 10:25:09 by epresa-c          #+#    #+#             */
/*   Updated: 2022/07/14 16:29:23 by epresa-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	is_redir(t_var *v, int *i, int *redir_stat, t_prompt *prompt)
{
	if (is_output_append(v, *i) == TRUE)
		proces_output_append(v, *i, redir_stat, prompt);
	if (is_here_doc(v, *i) == TRUE)
		proces_here_doc(v, *i, redir_stat, prompt);
	if (is_output_simple(v, *i) == TRUE)
		proces_output_simple(v, *i, redir_stat, prompt);
	if (is_input(v, *i) == TRUE)
		proces_input(v, *i, redir_stat, prompt);
}

int	is_output_append(t_var *v, int i)
{
	int	status;

	status = FALSE;
	if (v->s_split[i][0] == '>' && v->s_split[i + 1] \
		&& v->s_split[i + 1][0] == '>')
		status = TRUE;
	return (status);
}

int	is_here_doc(t_var *v, int i)
{
	int	status;

	status = FALSE;
	if (v->s_split[i][0] == '<' && v->s_split[i + 1] \
	&& v->s_split[i + 1][0] == '<')
		status = TRUE;
	return (status);
}

int	is_output_simple(t_var *v, int i)
{
	int	status;

	status = FALSE;
	if (v->s_split[i][0] == '>' && v->s_split[i + 1] \
		&& v->s_split[i + 1][0] != '>')
		status = TRUE;
	return (status);
}

int	is_input(t_var *v, int i)
{
	int	status;

	status = FALSE;
	if (v->s_split[i][0] == '<' && v->s_split[i + 1] \
		&& v->s_split[i + 1][0] != '<')
		status = TRUE;
	return (status);
}
