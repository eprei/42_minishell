#include <stdio.h>

int count_words(char *str)
{
    int i = 0;
    int count1;
    int count2;
    int state = 0;

    if (!str)
        return (-1);
    count1 = 1;
    count2 = 1;
    while (str[i] != 0)
    {
        if (str[i] == '\"')
            state = !state;
        if (state == 0)
            count2 = count1;
        if (str[i] == ' ' && state == 0)
            count1++;
        if (str[i] == ' ' && state == 1)    
            count2++;
        i++;
    }
    if (state == 0)
        return (count1);
    else
        return (count2);
}

int main()
{
    char *str = "Esto es \"una prueba de siete\" palabras";

    printf("str words = %d\n", count_words(str));
    return 0;
}