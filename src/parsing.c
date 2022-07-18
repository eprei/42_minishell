/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epresa-c <epresa-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 10:25:09 by epresa-c          #+#    #+#             */
/*   Updated: 2022/07/18 15:53:11 by epresa-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	fn_parsing(t_var *v, t_prompt *prompt)
{
	int	i;
	int	ret_pipes_pid;

	ret_pipes_pid = 0;
	count_cmd(v, prompt);
	ret_pipes_pid = create_pipes(prompt);
	i = 0;
	while (i < prompt->n_cmds && i <= ret_pipes_pid \
	&& prompt->token_status != FAILED)
	{
		if (i == 0)
			prompt->cmds = start_t_cmd(prompt);
		if (i > 0)
			add_t_cmd(prompt);
		fill_t_cmd(v, prompt, i);
		i++;
	}
}

void	fn_error_token(t_prompt *prompt)
{
	prompt->token_status = FAILED;
	prompt->error_msg = SYNTAX_ERROR;
	print_error(prompt);
}

void	count_cmd(t_var *v, t_prompt *prompt)
{
	int	i;

	i = 0;
	while (v->s_split[i] && v->s_split[i + 1] != NULL)
	{
		if ((v->s_split[i][0] == '|' && v->s_split[i + 1][0] == '|'))
		{
			fn_error_token(prompt);
			return ;
		}
		if (v->s_split[i][0] == '|')
			prompt->n_cmds++;
		i++;
	}
	if (v->s_split[i][0] == '|')
		fn_error_token(prompt);
}
