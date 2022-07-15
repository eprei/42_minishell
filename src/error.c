/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epresa-c <epresa-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 10:25:09 by epresa-c          #+#    #+#             */
/*   Updated: 2022/07/15 14:33:52 by epresa-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	fn_echo_error(t_cmd *curr, char *subplit_i, char *err_msg)
{
	tab_free(curr->full_cmd);
	free(curr->full_cmd);
	curr->full_cmd = malloc(sizeof(char *) * 2);
	curr->full_cmd[0] = ft_strdup(subplit_i);
	curr->full_cmd[1] = NULL;
	curr->is_builtin = FALSE;
	free(curr->status);
	curr->status = NULL;
	curr->status = ft_strdup(err_msg);
	curr->exec_stat = -1;
	g_exit_status = 1;
	if (ft_strncmp(err_msg, "command not found", 17) == 0 \
	&& ft_strlen(err_msg) == 17)
		curr->exec_stat = 127;
	else if (ft_strncmp(err_msg, "no such a file or directory", 27) == 0 \
	&& ft_strlen(err_msg) == 27)
		curr->exec_stat = 1;
	else if (ft_strncmp(err_msg, "is a directory", 14) == 0 && \
	ft_strlen(err_msg) == 14)
		curr->exec_stat = 126;
}

void	print_error(t_prompt *prompt)
{
	if (prompt->error_msg == MALLOC_ERROR)
		ft_printf("minishell: malloc error\n");
	if (prompt->error_msg == ERROR_TOKEN)
		ft_printf("Error token\n");
	if (prompt->error_msg == ERROR_SYNTAX_PIPE_AT_START)
		ft_printf("minishell: syntax error near unexpected token \'|\'\n");
	if (prompt->error_msg == SYNTAX_ERROR_NEAR_UNEXPECTED_TOKEN)
		ft_printf("minishell: syntax error\n");
	prompt->error_msg = NO_ERROR;
	g_exit_status = 258;
}

void	print_error_token(t_var *v)
{
	ft_printf("Error token\n");
	free(v->line);
	v->line = NULL;
	g_exit_status = 258;
}

void	error_redir(t_prompt *prompt)
{
	prompt->token_status = FAILED;
	prompt->error_msg = SYNTAX_ERROR_NEAR_UNEXPECTED_TOKEN;
	print_error(prompt);
}
