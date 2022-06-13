
#include "../includes/minishell.h"

static int	ft_count_words_OLD(char *s, char *set, int count);

void    fn_sub_split(t_var *v)
{   
    char **aux;
    int index_split;
    int index_aux;
    int index_subsplit;
    int number_total_subsplits = 0;
    int j = 0;

    while (v->split[j] != 0)
    {
        number_total_subsplits++;
        number_total_subsplits += ft_count_words_OLD(v->split[j], ">|<", 0); \\trabajar SUBSPLIT
        printf("number_total_subsplits = %d\tsplit[%d] = %s\n", number_total_subsplits, j, v->split[j]);
        j++;
    }
    aux = malloc(sizeof(char *) * number_total_subsplits);

    index_split = 0;
    index_subsplit = 0;
    while (v->split[index_split] != 0)
    {   
        aux = ft_cmdsubsplit(v->split[index_split], ">|<");
        index_aux = 0;
        while (aux[index_aux] != 0)
        {
            v->subsplit[index_subsplit] = ft_strdup(aux[index_aux]);
            // free(aux[index_aux]);
            aux[index_aux] = NULL;
            index_subsplit++;
            index_aux++;
        }
        index_split++;
    }
}

static int	ft_count_words_OLD(char *s, char *set, int count)
{
	int		q[2];
	int		i;

	i = 0;
	q[0] = 0;
	q[1] = 0;
	while (s && s[i] != '\0')
	{
		count++;
		if (!ft_strchr(set, s[i]))
		{
			while ((!ft_strchr(set, s[i]) || q[0] || q[1]) && s[i] != '\0')
			{
				q[0] = (q[0] + (!q[1] && s[i] == '\'')) % 2;
				q[1] = (q[1] + (!q[0] && s[i] == '\"')) % 2;
				i++;
			}
			if (q[0] || q[1])
				return (-1);
		}
		else
			i++;
	}
	return (count);
}

static char	**ft_fill_array_OLD(char **aux, char *s, char *set, int i[3])
{
	int		q[2];

	q[0] = 0;
	q[1] = 0;
	while (s && s[i[0]] != '\0')
	{
		i[1] = i[0];
		if (!ft_strchr(set, s[i[0]]))
		{
			while ((!ft_strchr(set, s[i[0]]) || q[0] || q[1]) && s[i[0]])
			{
				q[0] = (q[0] + (!q[1] && s[i[0]] == '\'')) % 2;
				q[1] = (q[1] + (!q[0] && s[i[0]] == '\"')) % 2;
				i[0]++;
			}
		}
		else
			i[0]++;
		aux[i[2]++] = ft_substr(s, i[1], i[0] - i[1]);
	}
	return (aux);
}

char	**ft_cmdsubsplit(char const *s, char *set)
{
	char	**aux;
	int		nwords;
	int		i[3];

	i[0] = 0;
	i[1] = 0;
	i[2] = 0;
	if (!s)
		return (NULL);
	nwords = ft_count_words_OLD((char *)s, set, 0);
	if (nwords == -1)
		return (NULL);
	aux = malloc((nwords + 1) * sizeof(char *));
	if (aux == NULL)
		return (NULL);
	aux = ft_fill_array_OLD(aux, (char *)s, set, i);
	aux[nwords] = NULL;
	return (aux);
}