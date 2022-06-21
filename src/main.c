/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epresa-c <epresa-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 15:01:33 by Emiliano          #+#    #+#             */
/*   Updated: 2022/06/21 17:39:10 by epresa-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	init_mini_vars(t_var *v, t_prompt *prompt, char **envp)
{
	g_exit_status = 0;
	init_t_var_main(v);
	init_t_prompt(prompt, envp);
}

void	free_all_tabs(t_var *v)
{
	free(v->line);
	v->line = NULL;
	tab_free(v->split);
	v->split = NULL;
	tab_free(v->subsplit);
	v->subsplit = NULL;
}

int	main(int argc, char **argv, char **envp)
{
	t_var		v;
	t_prompt	prompt;

	(void)argv;
	init_mini_vars(&v, &prompt, envp);
	signal(SIGINT, signal_handler); // ctrl + C
	signal(SIGQUIT, SIG_IGN); // ctrl + '\'
	// CTRL+D = EOF of standard input, wich ends the proces; LEARN HOW TO HANDLE THIS
	while (argc == 1)
	{
		v.line = readline(prompt.prompt_text);
        add_history(v.line);
		fn_lexer(&v, &prompt);
		fn_parsing(&v, &prompt);
		print_list(&prompt);
		free_all_tabs(&v);
		free_t_cmd(&prompt);
	}
	return (0);
}
