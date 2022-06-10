#include "../includes/minishell.h"

void    init_count_words_struct(t_count_words *w)
{
    w->quote_type = NO_INIT;
    w->quote_status = CLOSED;
    w->counter = 0;
}

int    ft_count_words(const char *str, char *caracter)
{
    int i;
    t_count_words w;

    i = 0;
    init_count_words_struct(&w);
    while (str[i] != '\0')
    {
        if (str[i] != *caracter)
        {
            w.counter++;
            while (((str[i] != *caracter ) || w.quote_status == OPEN) && str[i] != '\0')
            {
                if (w.quote_type == NO_INIT && (str[i] == '\"' || str[i] == '\''))
                    w.quote_type = str[i];
                w.quote_status = (w.quote_status + (str[i] == w.quote_type)) % 2;
                w.quote_type = w.quote_type * (w.quote_status == OPEN);
                i++;
                // printf("quoute_type = %d\tquote_status = %d\tcounter = %d\n", w.quote_type, w.quote_status, w.counter);
            }
            if (w.quote_status == OPEN)
                return (-1);
        }
        else
            i++;
    }
    return (w.counter);
}

char	**ft_fill_array(char **aux, char const *s, char *set, int i[3])
{
	int		s_len;
	int		q[2];

	q[0] = 0;
	q[1] = 0;
	s_len = ft_strlen(s);
	while (s[i[0]])
	{
		while (ft_strchr(set, s[i[0]]) && s[i[0]] != '\0')
			i[0]++;
		i[1] = i[0];
		while ((!ft_strchr(set, s[i[0]]) || q[0] || q[1]) && s[i[0]])
		{
			q[0] = (q[0] + (!q[1] && s[i[0]] == '\'')) % 2;
			q[1] = (q[1] + (!q[0] && s[i[0]] == '\"')) % 2;
			i[0]++;
		}
		if (i[1] >= s_len)
			aux[i[2]++] = "\0";
		else
			aux[i[2]++] = ft_substr(s, i[1], i[0] - i[1]);
	}
	return (aux);
}

char	**ft_split_str_with_spaces_and_quotes(char const *s, char *caracter)
{
	char	**aux;
	int		count_words;
	int		i[3];

	i[0] = 0;
	i[1] = 0;
	i[2] = 0;
	if (!s)
		return (NULL);
	count_words = ft_count_words(s, caracter);
	if (count_words == -1)
		return (NULL);
	aux = malloc((count_words + 1) * sizeof(char *));
	if (aux == NULL)
		return (NULL);
	aux = ft_fill_array(aux, s, caracter, i);
	aux[count_words] = NULL;
	return (aux);
}

int main()
{

    const char *str = "Hola que \'tres palabras\' cuatro \'cinco en total\'";
  char espacio = ' ';
  char *p = &espacio;
    char **split;

//    printf("numero de palabras = %d\n", ft_split_str_with_spaces_and_quotes(str, p)); 
    split = ft_split_str_with_spaces_and_quotes(str, p);
    for (int i = 0; split[i]; i++)
        printf("split[%d] = %s\n", i, split[i]);
  return 0;
}