/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epresa-c <epresa-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 16:52:31 by epresa-c          #+#    #+#             */
/*   Updated: 2022/06/20 14:51:45 by epresa-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	init_count_words_struct(t_count_words *w)
{
	w->q_type = NO_INIT;
	w->q_status = CLOSED;
	w->count = 0;
	w->i = 0;
}

int	ft_count_words(const char *str, char *caracter)
{
	t_count_words	w;

	init_count_words_struct(&w);
	while (str[w.i] != '\0')
	{
		if (str[w.i] != *caracter)
		{
			w.count++;
			while (((str[w.i] != *caracter) || \
			w.q_status == OPEN) && str[w.i] != '\0')
			{
				if (w.q_type == NO_INIT && \
				(str[w.i] == '\"' || str[w.i] == '\''))
					w.q_type = str[w.i];
				w.q_status = (w.q_status + (str[w.i] == w.q_type)) % 2;
				w.q_type = w.q_type * (w.q_status == OPEN);
				w.i++;
			}
			if (w.q_status == OPEN)
				return (-1);
		}
		else
			w.i++;
	}
	return (w.count);
}

void	init_quote_parsing_struct(t_quote_parsing *q, char const *str)
	{
	q->i = 0;
	q->quote_simple = CLOSED;
	q->quote_double = CLOSED;
	q->str_idx = 0;
	q->tab_index = 0;
	q->s_len = ft_strlen(str);
}

void	ft_fill_split(char **splited, char const *str, char *caracter)
{
	t_quote_parsing	q;

	init_quote_parsing_struct(&q, str);
	while (str[q.i] != '\0')
	{
		while (str[q.i] == *caracter && str[q.i] != '\0')
			q.i++;
		q.str_idx = q.i;
		while ((str[q.i] != *caracter || q.quote_simple == OPEN \
		|| q.quote_double == OPEN) && str[q.i] != '\0')
		{
			q.quote_simple = (q.quote_simple + \
			(!q.quote_double && str[q.i] == '\'')) % 2;
			q.quote_double = (q.quote_double + \
			(!q.quote_simple && str[q.i] == '\"')) % 2;
			q.i++;
		}
		if (q.str_idx >= q.s_len)
			splited[q.tab_index++] = "\0";
		else
			splited[q.tab_index++] = ft_substr(str, q.str_idx, q.i - q.str_idx);
	}
}

char	**ft_split_str_with_spaces_and_quotes(char const *s)
{
	char	**aux;
	int		count_words;
	char	caracter;

	caracter = ' ';
	if (!s)
		return (NULL);
	count_words = ft_count_words(s, &caracter);
	if (count_words == -1)
		return (NULL);
	aux = malloc((count_words + 1) * sizeof(char *));
	if (aux == NULL)
		return (NULL);
	ft_fill_split(aux, s, &caracter);
	aux[count_words] = NULL;
	return (aux);
}
