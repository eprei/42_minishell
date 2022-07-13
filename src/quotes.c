/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epresa-c <epresa-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 15:01:32 by epresa-c          #+#    #+#             */
/*   Updated: 2022/07/13 13:26:01 by epresa-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	check_quotes_and_delete(t_prompt *prompt, t_var *v, int i)
{
	char			*aux;
	int				k;
	t_quote_parsing	q;

	init_quote_parsing_struct(&q, NULL);
	k = -1;
	aux = malloc((ft_strlen(v->s_split[i]) + 1) * sizeof(char));
	if (aux == NULL)
	{
		prompt->error_msg = MALLOC_ERROR;
		prompt->token_status = FAILED;
		return ;
	}
	while (v->s_split[i][q.i] != '\0')
	{
		update_quote_status(v->s_split[i], &q);
		if ((v->s_split[i][q.i] != '\"' || q.q_simple) && \
		(v->s_split[i][q.i] != '\'' || q.q_double) && ++k >= 0)
			aux[k] = v->s_split[i][q.i];
		q.i++;
	}
	aux[++k] = '\0';
	free(v->s_split[i]);
	v->s_split[i] = aux;
}

void	fn_delete_quotes(t_var *v, t_prompt *prompt)
{
	int	i;

	i = 0;
	while (v->s_split[i] != NULL)
	{
		check_quotes_and_delete(prompt, v, i);
		if (prompt->error_msg != NO_ERROR)
		{
			print_error(prompt);
			return ;
		}
		i++;
	}
}
