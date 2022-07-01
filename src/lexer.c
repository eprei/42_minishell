/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epresa-c <epresa-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 15:01:32 by epresa-c          #+#    #+#             */
/*   Updated: 2022/07/01 15:13:22 by epresa-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// int	check_quotes_and_delete(t_var *v, int i)
// {
// 	char	*aux;
// 	int		j;
// 	t_quote_parsing q;

// 	init_quote_parsing_struct(&q, NULL);
// 	j = 0;
// 	aux = malloc((ft_strlen(v->subsplit[i]) + 1) * sizeof(char));
// 	if (aux == NULL)
// 		return (MALLOC_ERROR);
// 	while (v->subsplit[i][j] != '\0')
// 	{
// 		update_quote_status(v->subsplit[i], &q);
// 		if ((s1[i[0]] != '\"' || squote) && (s1[i[0]] != '\'' || dquote) \
// 			&& ++i[1] >= 0)
// 			trimmed[i[1]] = s1[i[0]];
// 		aux[j] = v->subsplit[i][j + 1];
// 		j++;
// 	}
// 	aux[j] = '\0';
// 	free(v->subsplit[i]);
// 	v->subsplit[i] = aux;
// 	return (0);
// }

// int	fn_delete_quotes(t_var *v)
// {
// 	int	i;
// 	int	ret;

// 	i = 0;
// 	while(v->subsplit[i] != NULL)
// 	{
// 		ret = check_quotes_and_delete(v, i);
// 		if (ret == MALLOC_ERROR)
// 		{
// 			g_exit_status = MALLOC_ERROR;
// 			return (MALLOC_ERROR);
// 		}
// 		i++;
// 	}
// 	return (0);
// 	// what to do in case to malloc error. with this return valu???
// }

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
		fn_expander(v, prompt);
		// fn_delete_quotes(v);
		print_tab_with_str_name(v->subsplit, "v->subsplit after lexer"); // JUST TO PRINT INFO
        init_path(prompt);
	}
}
