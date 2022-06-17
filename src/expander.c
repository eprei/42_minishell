/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epresa-c <epresa-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 16:58:25 by epresa-c          #+#    #+#             */
/*   Updated: 2022/06/17 15:44:26 by epresa-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*expand_vars(char *subsplit_i)
{
	char	*tmp;
	char	*ptr;
	int		i;

	i = 0;
	ptr = subsplit_i;
	while (ptr[i])
	{
		if (ptr[i] == '$')
			printf("$ founded at i = [%d]\n", i);
		i++;
	}

	tmp = ft_strjoin(subsplit_i, "_add_var_");
	free(subsplit_i);
	return (tmp);
}

char	*expand_path(char *subsplit_i)
{
	char	*tmp;

	tmp = ft_strjoin(subsplit_i, "_add_path_");
	free(subsplit_i);
	return (tmp);
}

void	fn_expander(t_var *v)
{
	int i;

	i = 0;
	while (v->subsplit && v->subsplit[i])
	{
		v->subsplit[i] = expand_vars(v->subsplit[i]);
		v->subsplit[i] = expand_path(v->subsplit[i]);
		i++;
	}
}
