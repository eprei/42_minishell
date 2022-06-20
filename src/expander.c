/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epresa-c <epresa-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 16:58:25 by epresa-c          #+#    #+#             */
/*   Updated: 2022/06/20 17:41:49 by epresa-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*expand_vars(char *subsplit_i, t_prompt *prompt)
{
	t_quote_parsing q;
	// char *tmp;
	(void)prompt;

	init_quote_parsing_struct(&q, NULL);
	while (subsplit_i && subsplit_i[q.i])
	{
		update_quote_status(subsplit_i, &q);
		if (q.quote_simple == CLOSED && subsplit_i[q.i] == '$')
		{	printf("found en i = [%d]\n", q.i);
			// tmp = ft_strjoin(subsplit_i, get_env("LESS", prompt->envp));
			// free(subsplit_i);
			// subsplit_i = tmp;
		}
		q.i++;
	}
	return (subsplit_i);
}

void	update_quote_status(char *subsplit_i, t_quote_parsing *q)
{
	q->quote_simple = (q->quote_simple + (q->quote_double == CLOSED && subsplit_i[q->i] == '\'')) % 2;
	q->quote_double = (q->quote_double + (q->quote_simple == CLOSED && subsplit_i[q->i] == '\"')) % 2;
}

char	*expand_path(char *subsplit_i, char *str_home)
{
	char	*tmp;
	char	*add_path;
	t_quote_parsing q;

	init_quote_parsing_struct(&q, NULL);
	while (subsplit_i && subsplit_i[q.i])
	{
		update_quote_status(subsplit_i, &q);
		if (q.quote_simple == CLOSED && q.quote_double == CLOSED && subsplit_i[q.i] == '~' \
			 && (/*q.i == 0  || */subsplit_i[q.i - 1] != '$')) // fn to_ check i + 1 !alphanum, i-1!alphanum i o chequear si i+1 es /
			{
				tmp = ft_substr(subsplit_i, 0, q.i);
				add_path = ft_strjoin(tmp, str_home);
				free(tmp);
				tmp = ft_substr(subsplit_i, q.i + 1, ft_strlen(subsplit_i));
				free(subsplit_i);
				subsplit_i = ft_strjoin(add_path, tmp);
				free(tmp);
				free(add_path);
			}
		q.i++;
	}
	free(str_home);
	return (subsplit_i);
}

void	fn_expander(t_var *v, t_prompt *prompt)
{
	int i;

	i = 0;
	while (v->subsplit && v->subsplit[i])
	{
		v->subsplit[i] = expand_vars(v->subsplit[i], prompt);
		v->subsplit[i] = expand_path(v->subsplit[i], get_env("HOME", prompt->envp));
		i++;
	}
}
