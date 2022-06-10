/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Emiliano <Emiliano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 15:01:33 by Emiliano          #+#    #+#             */
/*   Updated: 2022/06/10 13:03:01 by Emiliano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	**ft_fill_array(char **aux, char const *s, char *set, int i[3])
{
	int		s_len;
	int		q[2];

	q = 0;
	q[1] = 0;
	s_len = ft_strlen(s);
	while (s[i[0]])
	{
		while (ft_strchr(set, s[i[0]]) && s[i[0]] != '\0')
			i[0]++;
		count1 = i[0];
		while ((!ft_strchr(set, s[i[0]]) || q || q[1]) && s[i[0]])
		{
			q = (q + (!q[1] && s[i[0]] == '\'')) % 2;
			q[1] = (q[1] + (!q && s[i[0]] == '\"')) % 2;
			i[0]++;
		}
		if (count1 >= s_len)
			aux[i[2]++] = "\0";
		else
			aux[i[2]++] = ft_substr(s, count1, i[0] - count1);
	}
	return (aux);
}

char	**ft_cmdtrim(char const *s, char *set)
{
	char	**aux;
	int		nwords;
	int		i[3];
	int		counts[2];

	i[0] = 0;
	i[1] = 0;
	i[2] = 0;
	counts[0] = 0;
	counts[1] = 0;
	if (!s)
		return (NULL);
	nwords = ft_count_words(s, set, counts);
	if (nwords == -1)
		return (NULL);
	aux = malloc((nwords + 1) * sizeof(char *));
	if (aux == NULL)
		return (NULL);
	aux = ft_fill_array(aux, s, set, i);
	aux[nwords] = NULL;
	return (aux);
}


char    *get_prompt(void)
{
    char    *str_get_info;
    char    *str_prompt;

    str_get_info = getenv("USER");
    str_prompt = ft_strjoin(str_get_info, "@minishell42$ ");
    // free(str_get_info);
    return (str_prompt);
}

int main(int argc, char **argv, char **envp)
{
    char        *line;
    char        **split;
    char        **expand;
    char        **subsplit;
    char        **final_str_trim;
    t_prompt    prompt;
    
    
    prompt.envp = envp;

    char    *prompt_txt = get_prompt();
    signal(SIGINT, ft_new_prompt); // ctrl + C
    signal(SIGQUIT, sig_quit); // ctrl + '\'
    // CTRL+D = EOF of standard input, wich ends the proces; LEARN HOW TO HANDLE THIS

    while (argc == 1)
    {
        line = readline(prompt_txt); // copy stdin to line
        // fn_add_history(line); // need to be coded or use the real add_history function
        split = ft_cmdtrim(line, " "); 
        // split = ft_split(line, ' ');  // split str 
        // expand = ft_expand_var(split); // expand variables
        // subsplit = ft_subsplit(expand); // another split if its needed for < > |
        // final_str_trim = ft_final_str_strim(subsplit); // delete 
        int i = 0;
        while (split[i])
        {
            printf("split bucle [%d] = %s\n\n ", i, split[i]);
            free(split[i]);
            i++;
        }
        free(line);
        free(split);
        // free(expand);
        // free(subsplit);
        // free(final_str_trim);    
    }
    return (0);
}

/********************** ESTRUCTURAS MARCHANDO **********************/
// int main(int argc, char **argv, char **envp)
// {
//     t_prompt prompt;
//     t_cmd   cmd1;
//     t_cmd   cmd2;
    
    
//     cmd1.full_cmd = ft_strdup("this is cmd 1\n");
//     cmd2.full_cmd = ft_strdup("this is cmd 2\n");
 
//     cmd1.next = &cmd2;
//     cmd2.next = NULL;

//     prompt.cmds = &cmd1;
//     prompt.envp = NULL;
//     prompt.pid = 0;

//     printf("cmd 1 = %s\n", prompt.cmds->full_cmd);        
//     printf("cmd 1 next = %p\n", prompt.cmds->next);        
//     printf("cmd 2 = %s\n", prompt.cmds->next->full_cmd);        
//     printf("cmd 2 next = %p\n", prompt.cmds->next->next);        
//     return (0);
// }