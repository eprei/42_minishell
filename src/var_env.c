#include "../includes/minishell.h"

extern int	gstatus;

int	env_var_exist(char *name, char **my_env)
{
	int	i;
	char	*var;

	i = 0;

	var = ft_strjoin(name, "=");
	while (my_env && my_env[i])
	{
		if (ft_strncmp(my_env[i], var, ft_strlen(var)) == 0)
			return (i);
		i++;
	}
	return (-1);
}
	

// int	export_builtin(t_cmd *cmd, char **my_env) //
// {
// 	int	is_var;
	
// 	is_var = env_var_exist(cmd->full_cmd[1], my_env);
// 	if (is_var == -1)
// 	{
// 		my_env = tab_add(my_env, ft_strjoin(cmd->full_cmd[1], cmd->full_cmd[2]));
// 	}
// 	else
// 	{
// 		free(my_env[is_var]);
// 		my_env[is_var] = ft_strjoin(cmd->full_cmd[1], cmd->full_cmd[2]);
// 	}
// 	return (0);
// }

char	*get_env(char *name, char **my_env)
{
	int		is;
	char	*ret;
	size_t	len;

	len = ft_strlen(name);
	is = env_var_exist(name, my_env);
	if (is == - 1)
		ret = NULL;
	else
		ret = ft_substr(my_env[is], len  + 1, ft_strlen(my_env[is]) - len - 1);
	return (ret);
}

int	unset_builtin(char *name, char **my_env)
{
	int	i;
	int	j;
	char	*var;
	char	**ret;
	int		len;

	if (my_env == 0)
		return (1);
	i = -1;
	j = 0;
	len = tablen(my_env);
	ret = (char **)malloc(sizeof(char *) *len);
	if (ret == 0)
			return(1);
	var = ft_strjoin(name, "=");
	while (my_env[++i] && j < len)
	{
		 if (ft_strncmp(my_env[i], var, (int)ft_strlen(var))== 0)
			printf("C est la bonne %d\n", i);
		if (ft_strncmp(my_env[i], var, (int)ft_strlen(var)) != 0)
			ret[j++] = my_env[i];
	}
	ret[j] = NULL;
	printf("%d\n", len);
	return (0);
}

int	set_env(char *name, char *value, char **my_env)
{
	int	is_var;
	char *temp;
	
	temp = ft_strjoin(name, "=");
	is_var = env_var_exist(name, my_env);
	if (is_var == -1)
	{
		my_env = tab_add(my_env, ft_strjoin(temp, value));
	}
	else
	{
		free(my_env[is_var]);
		my_env[is_var] = ft_strjoin(temp,value);
	}
	free(temp);
	return (0);
}	
