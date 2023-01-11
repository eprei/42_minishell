/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epresa-c <epresa-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 16:58:25 by epresa-c          #+#    #+#             */
/*   Updated: 2022/07/13 17:59:58 by epresa-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*get_var_name(char *str, t_prompt *prompt)
{
	char	*aux;
	char	*variable_name;
	int		length;

	length = 0;
	while (str[length] != 0)
	{
		if (ft_strchr("/~%^{}:; ", str[length]) != 0 && length != 0)
			break ;
		length++;
	}
	variable_name = ft_substr(str, 1, length);
	if (variable_name[0] == '?' && ft_strlen(variable_name) == 1)
		return (variable_name);
	else
		aux = get_env(variable_name, prompt->envp);
	free(variable_name);
	return (aux);
}

char	*get_var_name_dquotes(char *str, t_prompt *prompt, int *idx_after)
{
	char	*aux;
	char	*variable_name;
	int		length;

	length = 0;
	while (str[length])
	{
		if (ft_strchr("/~%^{}:;\'\" ", str[length]) != 0 && length != 0)
		{
			length--;
			break ;
		}
		length++;
	}
	variable_name = ft_substr(str, 1, length);
	if (variable_name[0] == '?' && ft_strlen(variable_name) == 1)
		return (variable_name);
	else
		aux = get_env(variable_name, prompt->envp);
	free(variable_name);
	*idx_after = length;
	return (aux);
}

char	*var_between_dquotes(char *s_split_i, t_prompt *prompt, t_q_pars *q)
{
	int		idx_after;
	char	*name;
	char	*tmp[3];

	idx_after = 0;
	tmp[0] = ft_substr(s_split_i, 0, q->i);
	name = get_var_name_dquotes(&s_split_i[q->i], prompt, &idx_after);
	if (name == NULL)
		name = ft_strdup("");
	if (ft_strncmp(name, "?", 1) == 0 && ft_strlen(name) == 1)
	{
		free(name);
		name = ft_strdup(ft_itoa(g_exit_status));
	}
	tmp[2] = ft_strjoin(tmp[0], name);
	free(tmp[0]);
	tmp[0] = ft_substr(s_split_i, q->i + idx_after + 1, \
	ft_strlen(s_split_i) - q->i - idx_after);
	tmp[1] = ft_strjoin(tmp[2], tmp[0]);
	free(tmp[2]);
	free(tmp[0]);
	free(name);
	return (tmp[1]);
}

char	*var_between_squotes(char *s_split_i, t_prompt *prompt, t_q_pars *q)
{
	char	*name;
	char	*tmp[2];

	tmp[0] = ft_substr(s_split_i, 0, q->i);
	name = get_var_name(&s_split_i[q->i], prompt);
	if (name == NULL)
		name = ft_strdup("");
	if (ft_strncmp(name, "?", 1) == 0 && ft_strlen(name) == 1)
	{
		free(name);
		name = ft_itoa(g_exit_status);
	}
	tmp[1] = ft_strjoin(tmp[0], name);
	free(tmp[0]);
	free(name);
	return (tmp[1]);
}
