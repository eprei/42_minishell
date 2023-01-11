/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epresa-c <epresa-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 15:34:47 by epresa-c          #+#    #+#             */
/*   Updated: 2022/07/13 13:07:15 by epresa-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*get_prompt(char **envp)
{
	char	*str_get_info;
	char	*str_prompt;

	str_get_info = get_env("USER", envp);
	if (str_get_info == NULL)
		str_get_info = ft_strdup("guest");
	str_prompt = ft_strjoin(str_get_info, "@minishell42$ ");
	free(str_get_info);
	return (str_prompt);
}

void	init_t_var_main(t_var *v)
{
	v->line = NULL;
	v->split = NULL;
	v->tmp = NULL;
	v->s_split = NULL;
	v->i = 0;
	v->j = 0;
}

void	init_t_prompt(t_prompt *prompt, char **envp)
{
	char	*tmp;
	char	*pwd;

	prompt->envp = init_envp(envp);
	pwd = get_env("PWD", prompt->envp);
	tmp = ft_strjoin(pwd, "/minishell");
	prompt->cmds = NULL;
	set_env("SHELL", tmp, prompt);
	free(tmp);
	free(pwd);
	prompt->pipes = NULL;
	prompt->pid = NULL;
	prompt->paths = NULL;
	prompt->prompt_text = get_prompt(prompt->envp);
	prompt->n_cmds = 1;
	prompt->stop = FALSE;
	prompt->error_msg = NO_ERROR;
	prompt->token_status = TRUE;
}

void	print_tab_with_str_name(char **tab, char *tab_name)
{
	int	i;

	i = 0;
	if (tab == NULL)
		return ;
	ft_printf("\n\t Printing %s\n", tab_name);
	while (tab && tab[i] != NULL)
	{
		ft_printf("\t%s[%d] = %s\n", tab_name, i, tab[i]);
		i++;
	}
	ft_printf("\n");
}
