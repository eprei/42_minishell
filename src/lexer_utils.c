/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epresa-c <epresa-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 15:34:47 by epresa-c          #+#    #+#             */
/*   Updated: 2022/07/01 14:59:28 by epresa-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*get_prompt(char **envp)
{
	char	*str_get_info;
	char	*str_prompt;
	char	*color;

	str_get_info = get_env("USER", envp);
	str_prompt = ft_strjoin(str_get_info, "@minishell42$ ");
	free(str_get_info);
    color = ft_strjoin("\033[1;92m\002", str_prompt);
	free(str_prompt);
	str_prompt = ft_strjoin(color, "\033[0m");
	free(color);
	return (str_prompt);
}

void	init_t_var_main(t_var *v)
{
	v->line = NULL;
	v->split = NULL;
	v->tmp = NULL;
	v->subsplit = NULL;
	v->i = 0;
	v->j = 0;
}

void	init_t_prompt(t_prompt *prompt, char **envp)
{
	prompt->cmds = NULL;
	prompt->envp = init_envp(envp);
	prompt->pipes = NULL;
	prompt->pid = NULL;
	prompt->paths = NULL;
	prompt->prompt_text = get_prompt(prompt->envp);
	prompt->n_cmds = 1;
	prompt->stop = FALSE;
	prompt->token_status = TRUE;
}

void	print_tab_with_str_name(char **tab, char *tab_name)
{
	int	i;

	i = 0;
	if (tab == NULL)
		return ;
	ft_printf("\n\t Printing %s\n", tab_name);
	while (tab && tab[i])
	{
		// ft_printf("\t%s[%d] = %s\taddress = %p\n", tab_name, i, tab[i], tab[i]);
		ft_printf("\t%s[%d] = %s\n", tab_name, i, tab[i]);
		i++;
	}
	ft_printf("\n");
}
