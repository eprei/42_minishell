/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epresa-c <epresa-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 10:25:09 by epresa-c          #+#    #+#             */
/*   Updated: 2022/07/01 15:32:04 by epresa-c         ###   ########.fr       */
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

void    add_t_cmd(t_prompt *prompt)
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

void    fn_echo_error(t_cmd *curr, char *subplit_i, char *err_msg)
{
   // curr->outfile = 2;
	tab_free(curr->full_cmd);
	free(curr->full_cmd);
    curr->full_cmd = malloc(sizeof(char *) * 2);
    curr->full_cmd[0] = ft_strdup(subplit_i);
	curr->full_cmd[1] = NULL;
	curr->is_builtin = FALSE;
	curr->status = ft_strdup(err_msg);
}

int	check_builtin(char *cmd)
{
	int is_builtin;

	is_builtin = FALSE;
	if (ft_strncmp(cmd, "echo", 4) == 0 && ft_strlen(cmd) == 4)
		is_builtin = TRUE;
	if (ft_strncmp(cmd, "cd", 2) == 0 && ft_strlen(cmd) == 2)
		is_builtin = TRUE;
	if (ft_strncmp(cmd, "pwd", 3) == 0 && ft_strlen(cmd) == 3)
		is_builtin = TRUE;
	if (ft_strncmp(cmd, "export", 6) == 0 && ft_strlen(cmd) == 6)
		is_builtin = TRUE;
	if (ft_strncmp(cmd, "unset", 5) == 0 && ft_strlen(cmd) == 5)
		is_builtin = TRUE;
	if (ft_strncmp(cmd, "env", 3) == 0 && ft_strlen(cmd) == 3)
		is_builtin = TRUE;
	if (ft_strncmp(cmd, "exit", 4) == 0 && ft_strlen(cmd) == 4)
		is_builtin = TRUE;
	return (is_builtin);
}

void	is_builtin_is_exit(t_cmd *curr, t_prompt *prompt, int i, t_var *v)
{
	if (check_builtin(curr->full_cmd[0]) == TRUE)
		curr->is_builtin = TRUE;
	if (ft_strncmp(curr->full_cmd[0], "exit", 4) == 0 && ft_strlen(curr->full_cmd[0]) == 4)
	{
		if (i == 0)
		{
			prompt->stop = TRUE;
			if (v->subsplit[i + 1] && ft_atoi(v->subsplit[i + 1]) <= INT_MAX \
				&& ft_atoi(v->subsplit[i + 1]) >= INT_MIN)
				g_exit_status = ft_atoi(v->subsplit[i + 1]);
		}
		curr->exec_stat = NON_EXECUTABLE;
	}
	else
		prompt->stop = FALSE;
}

void	is_redir(t_var *v, int *i, int *j, int *redir_status)
{
	if (v->subsplit[*i][0] == '>' && v->subsplit[*i + 1][0] == '>')
	{
		*redir_status = REDIR_OUTPUT_APPEND;
		printf("\tdetect REDIR_OUTPUT_APPEND at i = %d\n", *i);
		*i += 2;
		*j += 2;
	}
	if (v->subsplit[*i][0] == '<' && v->subsplit[*i + 1][0] == '<')
	{
		*redir_status = HERE_DOC;
		printf("\tdetect HERE_DOC at i = %d\n", *i);
		*i += 2;
		*j += 2;
	}
	if (v->subsplit[*i][0] == '>')
	{
		*redir_status = REDIR_OUTPUT_SIMPLE;
		printf("\tdetect REDIR_OUTPUT_SIMPLE at i = %d\n", *i);
		*i += 1;
		*j += 1;
	}
	if (v->subsplit[*i][0] =='<')
	{
		*redir_status = REDIR_INPUT;
		printf("\tdetect REDIR_INPUT at i = %d\n", *i);
		*i += 1;
		*j += 1;
	}
}

void	fill_cmd_with_redir(t_var *v, int *i, int redir_status, t_cmd *curr, int *open_redir_status)
{
	*open_redir_status = FALSE;

	if (redir_status == REDIR_OUTPUT_APPEND)
	{
		*open_redir_status = open_outfiles(v->subsplit[*i], TRUE, curr);
		ft_printf("open_redir_status of REDIR_OUTPUT_APPEND = %d\n", *open_redir_status);
	}
	else if (redir_status == REDIR_OUTPUT_SIMPLE)
	{
		*open_redir_status = open_outfiles(v->subsplit[*i], FALSE, curr);
		ft_printf("open_redir_status of REDIR_OUTPUT_SIMPLE = %d\n", *open_redir_status);
	}
	else if (redir_status == HERE_DOC)
	{
		*open_redir_status = open_in_files(NULL, v->subsplit[*i], curr);
		ft_printf("open_redir_status of HERE_DOC= %d\n", *open_redir_status);
	}
	else if (redir_status == REDIR_INPUT)
	{
		*open_redir_status = open_in_files(v->subsplit[*i], NULL, curr);
		ft_printf("OPEN REDIR STATUS of REDIR_INPUT= %d\n", *open_redir_status);
	}
	if (*open_redir_status == FALSE)
		fn_echo_error(curr, v->subsplit[*i], "no such a file or directory");
}

char	**cd_expantion_home(t_cmd *curr, char **envp)
{
	char	**aux;

	tab_free(curr->full_cmd);
	// to solve leaks
	aux = malloc(sizeof(char *) * 3);
	aux[0] = ft_strdup("cd");
	aux[1] = get_env("HOME", envp);
	aux[2] = NULL;
	return (aux);
}

void	fill_t_cmd(t_var *v, t_prompt *prompt)
{
	static int	i = 0;
	t_cmd	*curr;
	int		redir_status;
	int 	j;
	int		open_redir_status;
	static int	n_pipe = 0;

	j = 0;
	curr = prompt->cmds;
	while (curr->next != NULL)
			curr = curr->next;
	if (v->subsplit[i][0] == '|')
	{
		if (curr->prev->outfile == 1)
		{
			curr->prev->outfile = prompt->pipes[n_pipe][1];
			curr->infile = prompt->pipes[n_pipe][0];
			n_pipe++;
		}
		i++;
	}
	while (v->subsplit[i] != NULL && v->subsplit[i][0] != '|')
	{
		redir_status = FALSE;
		is_redir(v, &i, &j, &redir_status);
		if (redir_status != FALSE)
			fill_cmd_with_redir(v, &i, redir_status, curr, &open_redir_status);
		else
		{
			curr->full_cmd = tab_add(curr->full_cmd, v->subsplit[i]);
			is_builtin_is_exit(curr, prompt, i, v);
		}
		j++;
		i++;
	}
	if (ft_strncmp(curr->full_cmd[0], "cd", 2) == 0 && ft_strlen(curr->full_cmd[0]) == 2 && curr->full_cmd[1] == NULL)
		curr->full_cmd = cd_expantion_home(curr, prompt->envp); // TO SOLVE: LEAKS
	if (curr->infile != -1)
	{
		if (curr->full_cmd != NULL && curr->is_builtin == FALSE)
			curr->full_path = create_path(prompt->paths, curr->full_cmd[0]);
		if (curr->full_path == NULL && curr->is_builtin == FALSE)
			fn_echo_error(curr, v->subsplit[i - j], "command not found");
	}
	if (v->subsplit[i] == NULL)
		i = 0;
}

void	fn_parsing(t_var *v, t_prompt *prompt)
{
	int i;

	i = 0;
	while (v->subsplit[i] && v->subsplit[i + 1] != NULL)
	{
		if (v->subsplit[i][0] == '|')
			prompt->n_cmds++;
		i++;
	}
	create_pipes_pids(prompt);
	i = 0;
	while (i < prompt->n_cmds)
	{
		if (i == 0)
			prompt->cmds = start_t_cmd(prompt);
		if (i > 0)
			add_t_cmd(prompt);
		fill_t_cmd(v, prompt);
		i++;
	}
}

void	print_list(t_prompt *prompt)
{
	t_cmd	*curr;
	int		i;

	i = 0;
	curr = prompt->cmds;
	ft_printf("\n\t**** PRINTING LIST OF COMMANDS ****\n\n");
	while (curr != NULL)
	{
		ft_printf("cmd_[%d] \t address = %p\n", i, curr);
		print_tab_with_str_name(curr->full_cmd, "cmd->full_cmd");
		ft_printf("\tfull_path = %s\n", curr->full_path);
		ft_printf("\tinfile = %d\n", curr->infile);
		ft_printf("\toutfile = %d\n", curr->outfile);
		ft_printf("\tis_builtin = %d\n", curr->is_builtin);
		ft_printf("\tstatus = %s\n", curr->status);
		ft_printf("\texec_status = %d\n", curr->exec_stat);
		ft_printf("\tprev = %p\n", curr->prev);
		ft_printf("\tnext = %p\n", curr->next);
		curr = curr->next;
		i++;
	}
}
