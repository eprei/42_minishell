/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epresa-c <epresa-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 10:25:09 by epresa-c          #+#    #+#             */
/*   Updated: 2022/06/21 17:37:37 by epresa-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_cmd	*start_t_cmd(t_prompt *prompt)
{
	t_cmd	*new_node;

	new_node = malloc(sizeof(t_cmd));
	if (new_node == NULL)
		ft_printf("Error malloc: new node creation has failed\n");
	else
	{
		new_node->full_cmd = NULL;
		new_node->full_path = NULL;
		new_node->infile = STDIN_FILENO;
		new_node->outfile = STDOUT_FILENO;
		new_node->is_builtin = 0;
		new_node->status = 0;
		new_node->next = NULL;
		new_node->prev = NULL;
		prompt->cmds = new_node;
	}
	return (new_node);
}

t_cmd	*add_t_cmd(t_prompt *prompt)
{
	t_cmd	*new_node;
	t_cmd	*curr;

	curr = prompt->cmds;
	new_node = malloc(sizeof(t_cmd));
	while (curr->next != NULL)
		curr = curr->next;
	if (new_node == NULL)
		ft_printf("Error malloc: new node creation has failed\n");
	else
	{
		new_node->full_cmd = NULL;
		new_node->full_path = NULL;
		new_node->infile = STDIN_FILENO;
		new_node->outfile = STDOUT_FILENO;
		new_node->is_builtin = 0;
		new_node->status = 0;
		new_node->next = NULL;
		new_node->prev = curr;
		curr->next = new_node;
	}
	return (new_node);
}

int	count_cmds(t_prompt *prompt)
{
	t_cmd	*curr;
	int i;

	i = 0;
	curr = prompt->cmds;
	while (curr != NULL)
	{
		curr = curr->next;
		i++;
	}
	return (i);
}

void	fill_t_cmd(t_var *v, t_cmd *curr, int *is_last_cmd, t_prompt *prompt)
{
	int	i;
	static int cmd_limit = 0;

	i = 0;
	while (v->subsplit[i] != NULL)
	{
		curr->full_cmd = tab_add(curr->full_cmd, v->subsplit[i]);
		i++;
	}
	curr->full_path = create_path(prompt->paths, curr->full_cmd[0]);
	cmd_limit++;
	if (cmd_limit == 3)
		*is_last_cmd = TRUE;
}

void	fn_parsing(t_var *v, t_prompt *prompt)
{
	int	is_last_cmd;
	t_cmd	*curr;
	(void)v;
	is_last_cmd = FALSE;
	curr = start_t_cmd(prompt);
	fill_t_cmd(v, curr, &is_last_cmd, prompt);
	while (is_last_cmd == FALSE)
	{
		curr = add_t_cmd(prompt);
		fill_t_cmd(v, curr, &is_last_cmd, prompt);
	}
	prompt->n_cmds = count_cmds(prompt);
	ft_printf("n_cmd = %d\n", prompt->n_cmds);
}

void	print_list(t_prompt *prompt)
{
	t_cmd	*curr;
	int		i;

	i = 0;
	curr = prompt->cmds;
	while (curr != NULL)
	{
		ft_printf("\n\t**** PRINTING LIST OF COMMANDS ****\n\n");
		ft_printf("cmd_[%d] \t address = %p\n", i, curr);
		print_tab_with_str_name(prompt->cmds->full_cmd, "cmd->full_cmd");
		ft_printf("\tfull_path = %s\n", curr->full_path);
		ft_printf("\tinfile = %d\n", curr->infile);
		ft_printf("\toutfile = %d\n", curr->outfile);
		ft_printf("\tis_builtin = %d\n", curr->is_builtin);
		ft_printf("\tstatus = %d\n", curr->status);
		ft_printf("\tprev = %p\n", curr->prev);
		ft_printf("\tnext = %p\n", curr->next);
		curr = curr->next;
		i++;
	}
}

void	free_t_cmd(t_prompt *prompt)
{
	t_cmd	*curr;
	t_cmd	*aux;

	curr = prompt->cmds;
	while (curr != NULL)
	{
		aux = curr;
		curr = curr->next;
		free(aux);
	}
}
