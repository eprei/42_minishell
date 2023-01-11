/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epresa-c <epresa-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 15:01:33 by Emiliano          #+#    #+#             */
/*   Updated: 2022/07/15 16:42:21 by epresa-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	init_mini_vars(t_var *v, t_prompt *prompt, char **envp)
{
	init_t_var_main(v);
	init_t_prompt(prompt, envp);
}

int	check_line(char *line)
{
	int	i;

	i = 0;
	if (ft_strlen(line) == 0)
		return (FALSE);
	while (line[i])
	{
		if (32 < (int)line[i] && (int)line[i] < 127)
			return (TRUE);
		i++;
	}
	return (FALSE);
}

void	start_boucle(t_var *v, t_prompt *prompt)
{
	signals_at_start();
	echo_ctrl_off();
	v->line = readline(prompt->prompt_text);
	echo_ctrl_on();
}

int	main(__attribute__((unused)) int argc, \
	__attribute__((unused)) char **argv, char **envp)
{
	t_var		v;
	t_prompt	prompt;

	init_mini_vars(&v, &prompt, envp);
	while (prompt.stop == FALSE)
	{
		start_boucle(&v, &prompt);
		if (!v.line)
			prompt.stop = TRUE;
		else if (check_line(v.line) == TRUE)
		{
			signal(SIGINT, signal_handler2);
			add_history(v.line);
			fn_lexer(&v, &prompt);
			if (v.split != NULL && prompt.token_status != FAILED)
			{
				fn_parsing(&v, &prompt);
				if (prompt.token_status != FAILED)
					read_list(&prompt);
			}
			free_all_tabs_and_prompt(&v, &prompt);
		}
	}
	write(1, "exit\n", 6);
	exit (g_exit_status);
}
