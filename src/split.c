/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epresa-c <epresa-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 16:52:31 by epresa-c          #+#    #+#             */
/*   Updated: 2022/06/13 17:02:49 by epresa-c         ###   ########.fr       */
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

void	init_fill_array_struct(t_fill_array *f, char const *str)
	{
	f->i = 0;
	f->quote_simple = CLOSED;
	f->quote_double = CLOSED;
	f->str_idx = 0;
	f->tab_index = 0;
	f->s_len = ft_strlen(str);
}

void	ft_fill_array(char **splited, char const *str, char *caracter)
{
	t_fill_array	f;

	init_fill_array_struct(&f, str);
	while (str[f.i] != '\0')
	{
		while (str[f.i] == *caracter && str[f.i] != '\0')
			f.i++;
		f.str_idx = f.i;
		while ((str[f.i] != *caracter || f.quote_simple == OPEN \
		|| f.quote_double == OPEN) && str[f.i] != '\0')
		{
			f.quote_simple = (f.quote_simple + \
			(!f.quote_double && str[f.i] == '\'')) % 2;
			f.quote_double = (f.quote_double + \
			(!f.quote_simple && str[f.i] == '\"')) % 2;
			f.i++;
		}
		if (f.str_idx >= f.s_len)
			splited[f.tab_index++] = "\0";
		else
			splited[f.tab_index++] = ft_substr(str, f.str_idx, f.i - f.str_idx);
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
	ft_fill_array(aux, s, &caracter);
	aux[count_words] = NULL;
	return (aux);
}
