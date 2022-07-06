/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epresa-c <epresa-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 15:21:06 by olmartin          #+#    #+#             */
/*   Updated: 2022/06/23 16:25:19 by olmartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	env_var_exist(char *name, char **my_env)
{
	int		i;
	char	*var;

	i = 0;
	var = ft_strjoin(name, "=");
	while (my_env && my_env[i])
	{
		if (ft_strncmp(my_env[i], var, ft_strlen(var)) == 0)
		{
			free(var);
			return (i);
		}
		i++;
	}
	free(var);
	return (-1);
}

char	*get_env(char *name, char **my_env)
{
	int		is;
	char	*ret;
	size_t	len;

	len = ft_strlen(name);
	is = env_var_exist(name, my_env);
	if (is == -1)
		ret = NULL;
	else
		ret = ft_substr(my_env[is], len + 1, ft_strlen(my_env[is]) - len - 1);
	return (ret);
}

char	**set_env(char *name, char *value, char **my_env)
{
	int		is_var;
	char	*temp;

	temp = ft_strjoin(name, "=");
	is_var = env_var_exist(name, my_env);
	if (is_var == -1)
	{
		my_env = tab_add(my_env, ft_strjoin(temp, value));
	}
	else
	{
		free(my_env[is_var]);
		my_env[is_var] = ft_strjoin(temp, value);
	}
	free(temp);
/*	if (env_var_exist(name, my_env) == -1)
		return (1);
	else
		return (0);
*/
	return (my_env);
}
