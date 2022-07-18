/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epresa-c <epresa-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 15:01:32 by epresa-c          #+#    #+#             */
/*   Updated: 2022/07/18 15:54:03 by epresa-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	add_sub_splits_to_tab(t_var *v)
{
	v->tmp = ft_cmds_split(v->split[v->i], "<|>");
	v->j = 0;
	while (v->tmp[v->j] != NULL)
	{
		v->s_split = tab_add(v->s_split, v->tmp[v->j]);
		v->j++;
	}
	tab_free(v->tmp);
	free(v->tmp);
	v->tmp = NULL;
}

void	check_pipe_at_start(t_var *v, t_prompt *prompt)
{
	int	i;

	i = 0;
	if (v->s_split[0][0] == '|')
	{
		prompt->error_msg = ERROR_SYNTAX_PIPE_AT_START;
		print_error(prompt);
		prompt->token_status = FAILED;
		g_exit_status = 258;
	}
	while (v->s_split[i] != NULL)
	{
		if (v->s_split[i][0] == '(' || v->s_split[i][0] == ')')
		{
			prompt->error_msg = SYNTAX_ERROR;
			print_error(prompt);
			prompt->token_status = FAILED;
			g_exit_status = 258;
		}
		i++;
	}
}

void	fn_lexer(t_var *v, t_prompt *prompt)
{
	prompt->token_status = TRUE;
	v->split = ft_split_str_with_spaces_and_quotes(v->line, prompt);
	if (v->split == NULL)
		print_error_token(v);
	else
	{
		v->i = 0;
		while (v->split[v->i])
		{
			add_sub_splits_to_tab(v);
			v->i++;
		}
		check_pipe_at_start(v, prompt);
		fn_expander(v, prompt);
		fn_delete_quotes(v, prompt);
		if (v->s_split[1] == NULL && ft_strlen(v->s_split[0]) == 0)
		{
			free(v->s_split[0]);
			v->s_split[0] = ft_strdup(" ");
		}
		init_path(prompt);
	}
}
