/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epresa-c <epresa-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 15:01:33 by Emiliano          #+#    #+#             */
/*   Updated: 2022/06/16 15:21:26 by epresa-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*get_prompt(char **envp)
{
	char	*str_get_info;
	char	*str_prompt;

	str_get_info = get_env("USER", envp);
	str_prompt = ft_strjoin(str_get_info, "@minishell42$ ");
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
	prompt->pid = 0;
	prompt->prompt_text = get_prompt(prompt->envp);
}

void print_tab_with_str_name(char **tab, char *tab_name)
{
	int	i;

	i = 0;
	if (tab == NULL)
	{
		ft_printf("ERROR ft_printf: the array %s doesn't exist\n", tab_name);
		return;
	}
	ft_printf("\t Printing %s\n", tab_name);
	while (tab && tab[i])
	{
		ft_printf("%s[%d] = %s\n", tab_name, i, tab[i]);
		i++;
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_var		v;
	t_prompt	prompt;

	(void)argv;
	g_exit_status = 0;
	init_t_var_main(&v);
	init_t_prompt(&prompt, envp);
	signal(SIGINT, signal_handler); // ctrl + C
	signal(SIGQUIT, signal_handler); // ctrl + '\'
	// CTRL+D = EOF of standard input, wich ends the proces; LEARN HOW TO HANDLE THIS
	while (argc == 1)
	{
		v.line = readline(prompt.prompt_text);
		v.split = ft_split_str_with_spaces_and_quotes(v.line); //this functions return NULL if ther's a quote inconsistence
		if (v.split == NULL)
		{
			ft_printf("Error token\n");
			free(v.line);
			v.line = NULL;
		}
		else
		{
			v.i = 0;
			while (v.split[v.i])
			{
				v.tmp = ft_cmdsubsplit(v.split[v.i], "<|>");
				v.j = 0;
				while (v.tmp[v.j] != NULL)
				{
					v.subsplit = tab_add(v.subsplit, v.tmp[v.j]);
					v.j++;
				}
				tab_free(v.tmp);
				v.tmp = NULL;
				v.i++;
			}
			free(v.line);
			v.line = NULL;
			tab_free(v.split);
			v.split = NULL;
			print_tab_with_str_name(v.subsplit, "v.subsplit final");
			tab_free(v.subsplit);
			v.subsplit = NULL;
		}
	}
	return (0);
}
