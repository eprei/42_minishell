#include "../includes/minishell.h"

int	export_builtin(t_cmd *cmd, char **my_env) 
 {
 	int	is_var;
	
 	is_var = env_var_exist(cmd->full_cmd[1], my_env);
 	if (is_var == -1)
 	{
 		my_env = tab_add(my_env, ft_strjoin(cmd->full_cmd[1], cmd->full_cmd[2]));
 	}
 	else
 	{
 		free(my_env[is_var]);
 		my_env[is_var] = ft_strjoin(cmd->full_cmd[1], cmd->full_cmd[2]);
 	}
 	return (0);
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
		if (ft_strncmp(my_env[i], var, (int)ft_strlen(var)) != 0)
			ret[j++] = my_env[i];
		else
			printf("C est la bonne %d\n", i);
	}
	ret[j] = NULL;
	tab_free(my_env);
	my_env = ret;
	return (0);
}

void	env_builtin(t_prompt *s_pr)
{
	print_tab(s_pr->envp);
}
