/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epresa-c <epresa-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 16:58:25 by epresa-c          #+#    #+#             */
/*   Updated: 2022/07/13 17:59:50 by epresa-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	fn_expander(t_var *v, t_prompt *prompt)
{
	int	i;

	i = 0;
	while (v->s_split && v->s_split[i])
	{
		v->s_split[i] = expand_vars(v->s_split[i], prompt);
		v->s_split[i] = expand_path(v->s_split[i], \
		get_env("HOME", prompt->envp));
		i++;
	}
}

int	search_charset_index_inside_str(char *str, char *set)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (ft_strchr(set, str[i]))
			return (i);
		i++;
	}
	return (CHAR_NOT_FOUND);
}

char	*expand_vars(char *s_split_i, t_prompt *prompt)
{
	t_q_pars	q;
	char		*new;

	init_q_pars_struct(&q, NULL);
	while (s_split_i && s_split_i[q.i])
	{
		update_quote_status(s_split_i, &q);
		if (q.q_simple == CLOSED && q.q_double == CLOSED \
		&& s_split_i[q.i] == '$')
		{
			new = var_between_squotes(s_split_i, prompt, &q);
			free(s_split_i);
			s_split_i = new;
		}
		if (q.q_simple == CLOSED && q.q_double == OPEN && s_split_i[q.i] == '$')
		{
			new = var_between_dquotes(s_split_i, prompt, &q);
			free(s_split_i);
			s_split_i = new;
		}
		q.i++;
	}
	return (s_split_i);
}
