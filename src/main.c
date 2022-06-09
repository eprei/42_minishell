/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Emiliano <Emiliano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 15:01:33 by Emiliano          #+#    #+#             */
/*   Updated: 2022/06/09 14:27:19 by Emiliano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
    char        *str;
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
        str = readline(prompt_txt); // copy stdin to str
        split = ft_split(str, ' ');  // split str 
        // expand = ft_expand_var(split); // expand variables
        // subsplit = ft_subsplit(expand); // another split if its needed for < > |
        // final_str_trim = ft_final_str_strim(subsplit); // delete 
        
        ft_printf("str = %s\n", str);
        int i;
        for (i = 0; split[i]; i++)
            ft_printf("split[%d] = %s\n ", i, split[i]);
        
        free(str);
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