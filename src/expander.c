/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epresa-c <epresa-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 16:58:25 by epresa-c          #+#    #+#             */
/*   Updated: 2022/07/04 11:22:48 by epresa-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// TO DO: EXPAND VARS, SEE IF EXPAND ~ WORKS IN SPECIAL CASES LIKE ECHO ~/

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

char	*get_var_name_double_quotes(char *str, t_prompt *prompt, int *idx_after_var)
{
	char	*aux;
	char	*variable_name;
	int		length;

	length = 0;
	while (str[length] != 0)
	{
		if (ft_strchr("/~%^{}:;\'\" ", str[length]) != 0 && length != 0) // BUG TO FIX: when $ is in beetween double quotes
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
	*idx_after_var = length;
	return (aux);
}

char	*expand_vars(char *subsplit_i, t_prompt *prompt)
{
	t_quote_parsing	q;
	char			*tmp;
	char			*tmp2;
	char			*tmp3;
	char			*name;
	int				idx_after_var;

	init_quote_parsing_struct(&q, NULL);
	while (subsplit_i && subsplit_i[q.i])
	{
		update_quote_status(subsplit_i, &q);
		if (q.quote_simple == CLOSED && q.quote_double == CLOSED && subsplit_i[q.i] == '$')
		{
			tmp = ft_substr(subsplit_i, 0, q.i); // string before '$'
			name = get_var_name(&subsplit_i[q.i], prompt); // check if var exist or not
			if (name == NULL)
				name = ft_strdup("");
			if (ft_strncmp(name, "?", 1) == 0 && ft_strlen(name) == 1) // if $? , name gets the value of g_exit_status
			{
				free(name);
				name = ft_strdup(ft_itoa(g_exit_status));
			}
			free(subsplit_i);
			subsplit_i = ft_strjoin(tmp, name);
			free(tmp);
			free(name);
			name = NULL;
		}
		if (q.quote_simple == CLOSED && q.quote_double == OPEN && subsplit_i[q.i] == '$')
		{
			idx_after_var = 0;
			tmp = ft_substr(subsplit_i, 0, q.i); // string before '$'
			name = get_var_name_double_quotes(&subsplit_i[q.i], prompt, &idx_after_var); // check if var exist or not
			if (name == NULL)
				name = ft_strdup("");
			if (ft_strncmp(name, "?", 1) == 0 && ft_strlen(name) == 1) // if $? , name gets the value of g_exit_status
			{
				free(name);
				name = ft_strdup(ft_itoa(g_exit_status));
			}
			tmp3 = ft_strjoin(tmp, name);
			free(tmp);
			tmp = ft_substr(subsplit_i, q.i + idx_after_var + 1, ft_strlen(subsplit_i) - q.i - idx_after_var);
			tmp2 = ft_strjoin(tmp3, tmp);
			free(tmp3);
			free(tmp);
			tmp = NULL;
			free(subsplit_i);
			subsplit_i = tmp2;
			free(name);
			name = NULL;
		}
		q.i++;
	}
	return (subsplit_i);
}

void	update_quote_status(char *subsplit_i, t_quote_parsing *q)
{
	q->quote_simple = (q->quote_simple + \
	(q->quote_double == CLOSED && subsplit_i[q->i] == '\'')) % 2;
	q->quote_double = (q->quote_double + \
	(q->quote_simple == CLOSED && subsplit_i[q->i] == '\"')) % 2;
}

char	*expand_path(char *subsplit_i, char *str_home)
{
	char			*tmp;
	char			*add_path;
	t_quote_parsing	q;

	init_quote_parsing_struct(&q, NULL);
	while (subsplit_i && subsplit_i[q.i])
	{
		update_quote_status(subsplit_i, &q);
		if (q.quote_simple == CLOSED && q.quote_double == CLOSED && subsplit_i[q.i] == '~' \
			 && (/*q.i == 0  || */subsplit_i[q.i - 1] != '$')) // fn to_ check i + 1 !alphanum, i-1!alphanum i o chequear si i+1 es /
		{
			tmp = ft_substr(subsplit_i, 0, q.i);
			add_path = ft_strjoin(tmp, str_home);
			free(tmp);
			tmp = ft_substr(subsplit_i, q.i + 1, ft_strlen(subsplit_i));
			free(subsplit_i);
			subsplit_i = ft_strjoin(add_path, tmp);
			free(tmp);
			free(add_path);
		}
		q.i++;
	}
	free(str_home);
	return (subsplit_i);
}

void	pars_expand_status(char *subsplit_i, int *expand_status)
{
	static int	i = 0;

	(void)subsplit_i;
	if (i == 1)
		*expand_status = FINISHED;
	i++;
}

void	fn_expander(t_var *v, t_prompt *prompt)
{
	int	i;

	i = 0;
	while (v->subsplit && v->subsplit[i])
	{
		v->subsplit[i] = expand_vars(v->subsplit[i], prompt);
		v->subsplit[i] = expand_path(v->subsplit[i], \
		get_env("HOME", prompt->envp));
		i++;
	}
}
