/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epresa-c <epresa-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 10:25:09 by epresa-c          #+#    #+#             */
/*   Updated: 2022/07/12 16:30:23 by epresa-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	fn_parsing(t_var *v, t_prompt *prompt)
{
	int	i;

	i = 0;
	while (v->s_split[i] && v->s_split[i + 1] != NULL)
	{
		if ((v->s_split[i][0] == '|' && v->s_split[i + 1][0] == '|'))
		{
			prompt->token_status = FAILED;
			prompt->error_msg = SYNTAX_ERROR_NEAR_UNEXPECTED_TOKEN;
			print_error(prompt);
			return ;
		}
		if (v->s_split[i][0] == '|')
			prompt->n_cmds++;
		i++;
	}
	if (v->s_split[i][0] == '|')
	{
		prompt->token_status = FAILED;
		prompt->error_msg = SYNTAX_ERROR_NEAR_UNEXPECTED_TOKEN;
		print_error(prompt);
		return ;
	}
	create_pipes_pids(prompt);
	i = 0;
	while (i < prompt->n_cmds && prompt->token_status != FAILED)
	{
		if (i == 0)
			prompt->cmds = start_t_cmd(prompt);
		if (i > 0)
			add_t_cmd(prompt);
		fill_t_cmd(v, prompt, i);
		i++;
	}
}
