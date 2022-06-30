/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epresa-c <epresa-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 15:01:32 by epresa-c          #+#    #+#             */
/*   Updated: 2022/06/30 17:38:12 by epresa-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	print_error_token(t_var *v)
{
	ft_printf("Error token\n");
	free(v->line);
	v->line = NULL;
}

void	fn_lexer(t_var *v, t_prompt *prompt)
{
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
				write(1, "syntax error near unexpected token\n", 36);
				// exit(-1);
				prompt->token_status = FAILED;
			}
		fn_expander(v, prompt);
		// fn_delete_quotes(v); TO MAKE
		print_tab_with_str_name(v->subsplit, "v->subsplit after lexer"); // JUST TO PRINT INFO
        init_path(prompt);
	}
}
