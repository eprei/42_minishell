/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epresa-c <epresa-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 16:58:25 by epresa-c          #+#    #+#             */
/*   Updated: 2022/07/06 12:28:53 by epresa-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	update_quote_status(char *subsplit_i, t_quote_parsing *q)
{
	q->quote_simple = (q->quote_simple + \
	(q->quote_double == CLOSED && subsplit_i[q->i] == '\'')) % 2;
	q->quote_double = (q->quote_double + \
	(q->quote_simple == CLOSED && subsplit_i[q->i] == '\"')) % 2;
}

char	*expand_path(char *subsplit_i, char *str_home)
{
	char			*tmp;
	char			*add_path;
	t_quote_parsing	q;

	init_quote_parsing_struct(&q, NULL);
	while (subsplit_i && subsplit_i[q.i])
	{
		update_quote_status(subsplit_i, &q);
		if (q.quote_simple == CLOSED && q.quote_double == CLOSED \
		&& subsplit_i[q.i] == '~' && (/*q.i == 0  || */subsplit_i[q.i - 1] != '$'))
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

void	pars_expand_status(char *subsplit_i, int *expand_status)
{
	static int	i = 0;

	(void)subsplit_i;
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
