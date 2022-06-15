#include "../includes/minishell.h"

extern int	gstatus;
char **init_test(char **envp);


int main(int argc, char **argv, char **envp)
{
	t_cmd	mystruct;
	char	**my_env;
	char	**dest;
	int		a;

	(void)a;
	(void)argc;
	(void)argv;
	mystruct.full_cmd = malloc(sizeof(char *) * 3);
	mystruct.full_cmd[0] = ft_strjoin("export" ,"");
	mystruct.full_cmd[1] = ft_strjoin("TXT", "");
	mystruct.full_cmd[2] = ft_strjoin("=LALALA","");
	my_env = init_envp(envp); //fonction normale
//	my_env = init_test(envp); //version test 4 var
	print_tab(my_env);
	dest = malloc(sizeof(char*) * 5);
	//printf("delone\n");
/*	dest = tab_delone(my_env, dest, 3);
	print_tab(dest);
	printf("fin print dest apres delone\n");
	print_tab(dest);
//	mini_pwd(my_env);
	printf("LA var, ancienne valeur: %s\n", get_env("TXT", my_env));
	a = tablen(my_env);
	printf("slen avant tabadd: %d\n", a);
	//tab_free(dest);
//	dest = tab_add(my_env, ft_strjoin(mystruct.full_cmd[1], mystruct.full_cmd[2])); 
// 	a = set_env(ft_strjoin("DDD", ""), ft_strjoin("TOTOTOT", ""), my_env);
	printf("LA var, nouvelle valeur: %s\n", get_env("DDD", dest));
	export_builtin(&mystruct, my_env);
	print_tab(my_env);
	printf("LA var, nouvelle 2 valeur: %s\n", get_env("TXT", dest));
//	ft_print_tab_model(my_env);
//	ft_putendl_fd("Test du putendl\n",0);
//*/	
	unset_builtin("HOME", my_env);
	printf("apres unset\n");
	print_tab(my_env);
	printf("LA var, apres unset %sZZ\n", get_env("TXT", my_env));
/*	mystruct.full_cmd[1] = "libft/";
	mini_cd(&mystruct, my_env);
	mini_pwd(my_env);

	a = env_var_exist("TXT", my_env);;
	printf("TXT existe: %d\n", a);
	tab_free(my_env);
	printf("apres free my_env\n");
	tab_free(dest);
	printf("apres free dest\n");
	tab_free(mystruct.full_cmd);
	free(mystruct.full_cmd);
	printf("apres free my_struct\n");
	while (1)
		;
*/	return (0);
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
