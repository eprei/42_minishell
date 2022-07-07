/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epresa-c <epresa-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 16:58:25 by epresa-c          #+#    #+#             */
/*   Updated: 2022/07/07 10:27:51 by epresa-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	update_quote_status(char *s_split_i, t_quote_parsing *q)
{
	q->q_simple = (q->q_simple + \
	(q->q_double == CLOSED && s_split_i[q->i] == '\'')) % 2;
	q->q_double = (q->q_double + \
	(q->q_simple == CLOSED && s_split_i[q->i] == '\"')) % 2;
}

char	*expand_path(char *s_split_i, char *str_home)
{
	char			*tmp;
	char			*add_path;
	t_quote_parsing	q;

	if (str_home == NULL)
		str_home = ft_strdup("");
	init_quote_parsing_struct(&q, NULL);
	while (s_split_i && s_split_i[q.i])
	{
		update_quote_status(s_split_i, &q);
		if (q.q_simple == CLOSED && q.q_double == CLOSED \
		&& s_split_i[q.i] == '~' && (s_split_i[q.i - 1] != '$'))
		{
			tmp = ft_substr(s_split_i, 0, q.i);
			add_path = ft_strjoin(tmp, str_home);
			free(tmp);
			tmp = ft_substr(s_split_i, q.i + 1, ft_strlen(s_split_i));
			free(s_split_i);
			s_split_i = ft_strjoin(add_path, tmp);
			free(tmp);
			free(add_path);
		}
		q.i++;
	}
	free(str_home);
	return (s_split_i);
}

void	pars_expand_status(char *s_split_i, int *expand_status)
{
	static int	i = 0;

	(void)s_split_i;
	if (i == 1)
		*expand_status = FINISHED;
	i++;
}

char	**cd_expantion_home(t_cmd *curr, char **envp)
{
	char	**aux;

	tab_free(curr->full_cmd);
	aux = malloc(sizeof(char *) * 3);
	aux[0] = ft_strdup("cd");
	aux[1] = get_env("HOME", envp);
	aux[2] = NULL;
	return (aux);
}
