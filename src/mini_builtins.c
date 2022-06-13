#include "minishell.h"

extern int gstatus;

int	mini_pwd(char **my_env) //OK
{
	char	*buffer;

	buffer = NULL;
//	buffer = get_cwd(NULL, 0);
	buffer = get_env("PWD", my_env); 
	if (buffer != NULL)
		ft_putendl_fd(buffer, 0);
	free(buffer);
	return (0);
}

int	mini_cd(t_cmd *cmd, char **my_env)
{
	char *dest;
	char *buffer;

	int	res;

	buffer = ft_strdup(get_env("PWD", my_env)); 
	dest = cmd->full_cmd[1];

	if (dest == NULL)
		dest = get_env("HOME", my_env);
	if (dest == NULL)
		return (-1);
	if (access(dest, F_OK) == 0)
		res = chdir(dest);
	if (res == 0)
	{
		set_env("OLDPWD", buffer, my_env);
		set_env("PWD", dest, my_env);
	}
	return (res);
}

