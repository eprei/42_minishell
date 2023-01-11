/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_redir_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epresa-c <epresa-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 10:25:09 by epresa-c          #+#    #+#             */
/*   Updated: 2022/07/14 16:26:31 by epresa-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	proces_output_append(t_var *v, int i, int *redir_stat, t_prompt *prompt)
{
	if (v->s_split[i + 2] != NULL && \
	ft_strchr("~%^{}:; |\\", v->s_split[i + 2][0]) == 0)
		*redir_stat = REDIR_OUTPUT_APPEND;
	else
		error_redir(prompt);
}

void	proces_here_doc(t_var *v, int i, int *redir_stat, t_prompt *prompt)
{
	if (v->s_split[i + 2] != NULL && \
	ft_strchr("~%^{}:; |\\", v->s_split[i + 2][0]) == 0)
		*redir_stat = HERE_DOC;
	else
		error_redir(prompt);
}

void	proces_output_simple(t_var *v, int i, int *redir_stat, t_prompt *prompt)
{
	if (v->s_split[i + 1] != NULL && \
	ft_strchr("~%^{}:; |\\", v->s_split[i + 1][0]) == 0)
		*redir_stat = REDIR_OUTPUT_SIMPLE;
	else
		error_redir(prompt);
}

void	proces_input(t_var *v, int i, int *redir_stat, t_prompt *prompt)
{
	if (v->s_split[i + 1] != NULL && \
	ft_strchr("~%^{}:; |\\", v->s_split[i + 1][0]) == 0)
		*redir_stat = REDIR_INPUT;
	else
		error_redir(prompt);
}
