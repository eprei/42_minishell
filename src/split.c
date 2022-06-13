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

void    init_fill_array_struct(t_fill_array *f, char const *str)
{
    f->i = 0;
    f->quote_simple = CLOSED;
    f->quote_double = CLOSED;
    f->start_index = 0;
    f->tab_index = 0;
    f->s_len = ft_strlen(str);
}

void    ft_fill_array(char **splited, char const *str, char *caracter)
{
    t_fill_array f;

    init_fill_array_struct(&f, str);
	while (str[f.i] != '\0')
	{
        while (str[f.i] == *caracter && str[f.i] != '\0')
			f.i++;
		f.start_index = f.i;
		while ((str[f.i] != *caracter || f.quote_simple == OPEN || f.quote_double == OPEN ) && str[f.i] != '\0')
		{
			f.quote_simple = (f.quote_simple + (!f.quote_double && str[f.i] == '\'')) % 2;
			f.quote_double = (f.quote_double + (!f.quote_simple && str[f.i] == '\"')) % 2;
			f.i++;
		}
		if (f.start_index >= f.s_len)
			splited[f.tab_index++] = "\0";
        else
			splited[f.tab_index++] = ft_substr(str, f.start_index, f.i - f.start_index);
    }
}

char	**ft_split_str_with_spaces_and_quotes(char const *s)
{
	char	**aux;
	int		count_words;
    char    caracter = ' ';

	if (!s)
		return (NULL);
	count_words = ft_count_words(s, &caracter);
	if (count_words == -1)
       	return (NULL);
	aux = malloc((count_words + 1) * sizeof(char *));
	if (aux == NULL)
		return (NULL);
	ft_fill_array(aux, s, &caracter);
	aux[count_words] = NULL;
	return (aux);
}
/*
int main()
{

    const char *str = "Hola \"que para \" ver \'tres palabras\' cuatro \'cinco en total\'";
  char espacio = ' ';
    char **split;

//    printf("numero de palabras = %d\n", ft_split_str_with_spaces_and_quotes(str, p)); 
    // split = ft_split_str_with_spaces_and_quotes(str, &espacio);
    split = ft_split_str_with_spaces_and_quotes(str);
    if (split == NULL)
        printf("error token\n");
    else
    {
        for (int i = 0; split[i]; i++)
            printf("split no char[%d] = %s\n", i, split[i]);
    }
  return 0;
}*/