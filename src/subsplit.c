/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epresa-c <epresa-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 11:44:35 by epresa-c          #+#    #+#             */
/*   Updated: 2022/07/04 11:04:53 by epresa-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	ft_count_words_with_set(char *str, char *set)
{
	t_count_words	w;

	init_count_words_struct(&w);
	while (str && str[w.i] != '\0')
	{
		w.count++;
		if (!ft_strchr(set, str[w.i]))
		{
			while ((!ft_strchr(set, str[w.i]) || w.q_type != NO_INIT \
			|| w.q_status == OPEN) && str[w.i] != '\0')
			{
				w.q_type = (w.q_type + (!w.q_status && str[w.i] == '\'')) % 2;
				w.q_status = (w.q_status + (!w.q_type && str[w.i] == '\"')) % 2;
				w.i++;
			}
			if (w.q_type != NO_INIT || w.q_status == OPEN)
				return (-1);
		}
		else
			w.i++;
	}
	return (w.count);
}

void	init_indexs(int index[2])
{
	index[0] = 0;
	index[1] = 0;
}

static char	**ft_fill_subsplit(char **aux, char *str, char *set)
{
	t_q_pars	q;
	int			index[2];

	init_indexs(index);
	init_q_pars_struct(&q, str);
	while (str && str[q.i] != '\0')
	{
		index[0] = q.i;
		if (!ft_strchr(set, str[q.i]))
		{
			while ((ft_strchr(set, str[q.i]) == 0 || \
			q.q_simple == OPEN || q.q_double == OPEN) && str[q.i])
			{
				q.q_simple = (q.q_simple + \
				(!q.q_double && str[q.i] == '\'')) % 2;
				q.q_double = (q.q_double + \
				(!q.q_simple && str[q.i] == '\"')) % 2;
				q.i++;
			}
		}
		else
			q.i++;
		aux[index[1]++] = ft_substr(str, index[0], q.i - index[0]);
	}
	return (aux);
}

char	**ft_cmds_split(char const *str, char *set)
{
	char	**aux;
	int		nwords;

	if (!str)
		return (NULL);
	nwords = ft_count_words_with_set((char *)str, set);
	if (nwords == -1)
		return (NULL);
	aux = malloc((nwords + 1) * sizeof(char *));
	if (aux == NULL)
		return (NULL);
	aux = ft_fill_subsplit(aux, (char *)str, set);
	aux[nwords] = NULL;
	return (aux);
}
