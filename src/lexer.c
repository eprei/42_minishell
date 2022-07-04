/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Emiliano <Emiliano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 15:01:32 by epresa-c          #+#    #+#             */
/*   Updated: 2022/07/03 21:49:35 by Emiliano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	check_quotes_and_delete(t_prompt *prompt, t_var *v, int i)
{
	char	*aux;
	int		j;
	int		k;
	t_quote_parsing q;

	init_quote_parsing_struct(&q, NULL);
	k = -1;
	j = 0;
	aux = malloc((ft_strlen(v->subsplit[i]) + 1) * sizeof(char));
	if (aux == NULL)
	{
		prompt->error_msg = MALLOC_ERROR;
		prompt->token_status = FAILED;
		return;
	}
	while (v->subsplit[i][j] != '\0')
	{
		update_quote_status(v->subsplit[i], &q);
		if ((v->subsplit[i][j] != '\"' || q.quote_simple) && (v->subsplit[i][j] != '\'' \
		 || q.quote_double)  && ++k >= 0 )
			aux[k] = v->subsplit[i][j];
		j++;
	}
	aux[++k] = '\0';
	free(v->subsplit[i]);
	v->subsplit[i] = aux;
}

void	print_error(t_prompt *prompt)
{
	if (prompt->error_msg == MALLOC_ERROR)
		ft_printf("minishell: malloc error\n");
	prompt->error_msg = NO_ERROR;
}

void	fn_delete_quotes(t_var *v, t_prompt *prompt)
{
	int	i;

	i = 0;
	while(v->subsplit[i] != NULL)
	{
		check_quotes_and_delete(prompt, v, i);
		if (prompt->error_msg != NO_ERROR)
		{
			print_error(prompt);
			return;
		}
		i++;
	}
}

void	print_error_token(t_var *v)
{
	ft_printf("Error token\n");
	free(v->line);
	v->line = NULL;
}

void	fn_lexer(t_var *v, t_prompt *prompt)
{
	int	ret;

	ret = 0;
	prompt->token_status = TRUE;
	v->split = ft_split_str_with_spaces_and_quotes(v->line); //this functions return NULL if ther's a quote inconsistence
	if (v->split == NULL)
	{
		print_error_token(v);
		return ;
	}
	else
	{
		v->i = 0;
		while (v->split[v->i])
		{
			v->tmp = ft_cmdsubsplit(v->split[v->i], "<|>");
			v->j = 0;
			while (v->tmp[v->j] != NULL)
			{
				v->subsplit = tab_add(v->subsplit, v->tmp[v->j]);
				v->j++;
			}
			tab_free(v->tmp);
            free(v->tmp);
			v->tmp = NULL;
			v->i++;
		}
		if (v->subsplit[0][0] == '|')
			{
				write(1, "minishell: syntax error near unexpected token \'|\'\n", 51);
				prompt->token_status = FAILED;
			}
		print_tab_with_str_name(v->subsplit, "v->subsplit before expander"); // JUST TO PRINT INFO
		fn_expander(v, prompt);
		print_tab_with_str_name(v->subsplit, "v->subsplit after expander and before delete quotes"); // JUST TO PRINT INFO
		fn_delete_quotes(v, prompt); // bug << echo loco"que'$HOME'pasa" >> && << >> ver iterm
		print_tab_with_str_name(v->subsplit, "v->subsplit after delete quotes"); // JUST TO PRINT INFO
		init_path(prompt);
	}
}
