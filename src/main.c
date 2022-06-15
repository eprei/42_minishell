/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epresa-c <epresa-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 15:01:33 by Emiliano          #+#    #+#             */
/*   Updated: 2022/06/15 16:52:38 by epresa-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	tab_free_emi(char **tab) // the only difference with the original is de tab = NULL at 26th line
{
		int	i;

		i = 0;
		while (tab && tab[i])
		{
			free(tab[i]);
			i++;
		}
		free(tab);
		tab = NULL;
}

static char	**tab_add_emi(char **src, char *add) //the only diference with the original it's the tab_free_emi at 36th line
{
	char	**dest;
	int		len;
	int		i;

	if (!add)
		return (src);
	len = tablen(src);
	dest = (char **)malloc(sizeof(char *) * (len + 2));
	if (dest == NULL)
		return (src);
	i = 0;
	while (i < len)
	{
		dest[i] = ft_strdup(src[i]);
		//test si dup OK ?
		i++;
	}
	dest[i++] = add;
	dest[i] = NULL;
	tab_free_emi(src);
	return (dest);
}

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
}

void	init_t_prompt(t_prompt *prompt, char **envp)
{
	prompt->cmds = NULL;
	prompt->envp = init_envp(envp);
	prompt->pid = 0;
	prompt->prompt_text = get_prompt(prompt->envp);
}

void print_tab(char **tab, char *tab_name)
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
		ft_printf("\nv.line = %s\n\n", v.line);
		v.split = ft_split_str_with_spaces_and_quotes(v.line); //this functions return NULL if ther's a quote inconsistence
		if (v.split == NULL)
		{
			ft_printf("Error token\n");
			free(v.line);
		}
		free(v.line);
		v.line = NULL;
		print_tab(v.split, "v.split");
		int i = 0;

		while (v.split[i])
		{
			printf("\n");
			v.tmp = ft_cmdsubsplit(v.split[i], "<|>");
			int	j = 0;
			printf("\t****** PRINTING tmp[%d] ******\n", i);
			while (v.tmp[j] != NULL)
			{
				printf("\tj = %d\n", j);
				printf("tmp[%d] = %s\n", j, v.tmp[j]);
				v.subsplit = tab_add_emi(v.subsplit, v.tmp[j]);
				j++;
			}
	//		tab_free_emi(tmp);
			i++;
		}
		print_tab(v.subsplit, "v.subsplit");
		tab_free(v.subsplit);
	}
	return (0);
}
