#include "minishell.h"

char **init_envp(char **envp)
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
	while (++i < len)
	{
		dest[i] = ft_strdup(envp[i]);
		if (dest[i] == NULL)
				return (NULL);
	}
	dest[i] = NULL;
	return (dest);
}

