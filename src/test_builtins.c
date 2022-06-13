#include "../includes/minishell.h"

extern int	gstatus;
char **init_test(char **envp);


int main(int argc, char **argv, char **envp)
{
	t_cmd	mystruct;
	char	**my_env;
	
	(void)argc;
	(void)argv;
	mystruct.full_cmd = malloc(sizeof(char *) * 3);
/*	mystruct.full_cmd[0] = malloc(sizeof(char) * 10);
	mystruct.full_cmd[1] = malloc(sizeof(char) * 10);
	mystruct.full_cmd[2] = malloc(sizeof(char) * 10);
*///	my_env = init_envp(envp);
	my_env = init_test(envp);
//	ft_print_tab_model(my_env);
	mini_pwd(my_env);
	printf("LA var, ancienne valeur: %s\n", get_env("TXT", my_env));
	mystruct.full_cmd[1] = ft_strjoin("TXT", "");
	mystruct.full_cmd[2] = ft_strjoin("=LALALA";"")
/*	export_builtin(&mystruct, my_env);
//	ft_print_tab_model(my_env);
//	ft_putendl_fd("Test du putendl\n",0);
	printf("LA var, nouvelle valeur: %s\n", get_env("TXT", my_env));
	unset_builtin("TXT", my_env);
	printf("LA var, apres unset %sZZ\n", get_env("TXT", my_env));
	mystruct.full_cmd[1] = "libft/";
	mini_cd(&mystruct, my_env);
	mini_pwd(my_env);
*/
	tab_free(&mystruct.full_cmd);
	return (0);
}

char **init_test(char **envp)
{
	char **dest;
	int	i;
	int	len;

	if (!envp)
			return (NULL);
	len = tablen(envp);
	dest = (char **)malloc(sizeof(char*) * (len + 1));
	if (dest == NULL)
			return (NULL);
	i = -1;
	while (++i < 4)
	{
		dest[i] = ft_strdup(envp[i]);
		if (dest[i] == NULL)
				return (NULL);
	}
	dest[i] = NULL;
	return (dest);
}
