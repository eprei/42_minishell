#include "../includes/minishell.h"

int	tablen(char **t)
{
	int	i;

	i = 0;
	while (t && t[i])
		i++;
	return (i);
}

char	**tab_add(char **src, char *add)
{
	char	**dest;
	int		len;
	int		i;

	if (!add)
		return (src);
	len = tablen(src);
	dest = (char **)malloc(sizeof(char *) * (len + 2));
	if (dest == NULL)
		return (src);
	i = 0;
	while (i < len)
	{
		dest[i] = ft_strdup(src[i]);
		//test si dup OK ?
		i++;
	}
	dest[i++] = add;
	dest[i] = NULL;
	tab_free(src);
	return (dest);
}

void	tab_free(char **tab)
{
		int	i;

		i = 0;
		while (tab[i])
		{
			free(tab[i]);
			i++;
		}
		free(tab);
		// tab = NULL;
}

