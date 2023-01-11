/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_t_cmd_management.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epresa-c <epresa-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 10:25:09 by epresa-c          #+#    #+#             */
/*   Updated: 2022/07/06 11:34:53 by epresa-c         ###   ########.fr       */
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
		new_node->is_builtin = FALSE;
		new_node->status = NULL;
		new_node->exec_stat = EXECUTABLE;
		new_node->next = NULL;
		new_node->prev = NULL;
		prompt->cmds = new_node;
	}
	return (new_node);
}

void	add_t_cmd(t_prompt *prompt)
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
		new_node->is_builtin = FALSE;
		new_node->status = NULL;
		new_node->exec_stat = EXECUTABLE;
		new_node->next = NULL;
		new_node->prev = curr;
		curr->next = new_node;
	}
}

int	count_cmds(t_prompt *prompt)
{
	t_cmd	*curr;
	int		i;

	i = 0;
	curr = prompt->cmds;
	while (curr != NULL)
	{
		curr = curr->next;
		i++;
	}
	return (i);
}
