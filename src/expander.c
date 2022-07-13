/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epresa-c <epresa-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 16:58:25 by epresa-c          #+#    #+#             */
/*   Updated: 2022/07/13 14:05:52 by epresa-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	fn_expander(t_var *v, t_prompt *prompt)
{
	int	i;

	i = 0;
	while (v->s_split && v->s_split[i])
	{
		v->s_split[i] = expand_vars(v->s_split[i], prompt);
		v->s_split[i] = expand_path(v->s_split[i], \
		get_env("HOME", prompt->envp));
		i++;
	}
}

int	search_charset_index_inside_str(char *str, char *set)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (ft_strchr(set, str[i]))
			return (i);
		i++;
	}
	return (CHAR_NOT_FOUND);
}

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
	while (str[length] != 0)
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

char	*expand_vars(char *s_split_i, t_prompt *prompt)
{
	t_quote_parsing	q;
	char			*tmp;
	char			*tmp2;
	char			*tmp3;
	char			*name;
	int				idx_after;

	init_quote_parsing_struct(&q, NULL);
	while (s_split_i && s_split_i[q.i])
	{
		update_quote_status(s_split_i, &q);
		if (q.q_simple == CLOSED && q.q_double == CLOSED && s_split_i[q.i] == '$')
		{
			tmp = ft_substr(s_split_i, 0, q.i);
			name = get_var_name(&s_split_i[q.i], prompt);
			if (name == NULL)
				name = ft_strdup("");
			if (ft_strncmp(name, "?", 1) == 0 && ft_strlen(name) == 1)
			{
				free(name);
				name = ft_itoa(g_exit_status);
			}
			free(s_split_i);
			s_split_i = ft_strjoin(tmp, name);
			free(tmp);
			free(name);
			name = NULL;
		}
		if (q.q_simple == CLOSED && q.q_double == OPEN && s_split_i[q.i] == '$')
		{
			idx_after = 0;
			tmp = ft_substr(s_split_i, 0, q.i);
			name = get_var_name_dquotes(&s_split_i[q.i], prompt, &idx_after);
			if (name == NULL)
				name = ft_strdup("");
			if (ft_strncmp(name, "?", 1) == 0 && ft_strlen(name) == 1)
			{
				free(name);
				name = ft_strdup(ft_itoa(g_exit_status));
			}
			tmp3 = ft_strjoin(tmp, name);
			free(tmp);
			tmp = ft_substr(s_split_i, q.i + idx_after + 1, ft_strlen(s_split_i) - q.i - idx_after);
			tmp2 = ft_strjoin(tmp3, tmp);
			free(tmp3);
			free(tmp);
			tmp = NULL;
			free(s_split_i);
			s_split_i = tmp2;
			free(name);
			name = NULL;
		}
		q.i++;
	}
	return (s_split_i);
}
